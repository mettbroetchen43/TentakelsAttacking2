//
// Purpur Tentakel
// 31.10.2022
//

#include "NewGameParameter.h"
#include "AppContext.h"
#include "Text.h"
#include "Title.h"
#include "Line.h"
#include "ClassicButton.h"
#include "UIEvents.hpp"
#include "SceneType.h"
#include "GameEventSettings.h"
#include "SliderAndInputLine.h"

enum class SliderType {
	PLANET_COUNT,
	DIMENSION_X,
	DIMENSION_Y,
	FLEET_SPEED,
	TARGET_ROUND,
};

void NewGameParameterScene::Initialize(Vector2 resolution) {
	AppContext_ty appContext{ AppContext::GetInstance() };

	// title
	m_elements.push_back(std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		resolution,
		false,
		appContext
	));


	// parameters
	auto parameterText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.2f),
		GetElementSize(0.3f, 0.1f),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_MID,
		0.07f,
		"Parameter"
	);
	// parameterText->RenderRectangle(true);
	m_elements.push_back(parameterText);

	// line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.5f, 0.3f),
		GetElementSize(0.0f, 0.65f),
		Alignment::TOP_MID,
		resolution,
		2.0f,
		WHITE
	));

	// events
	m_eventSettings = std::make_shared<GameEventSettings>(
		1,
		GetElementPosition(0.25f, 0.3f),
		GetElementSize(0.25f, 0.5f),
		Alignment::TOP_MID,
		resolution
	);
	m_eventSettings->SetActive(true, appContext);
	m_elements.push_back(m_eventSettings);


	          int ID = 100;
	constexpr int IDOffset = 100;
	constexpr float posX = 0.75f;
	          float posY = 0.3f;
	constexpr float offsetY = 0.1f;
	constexpr float sizeX = 0.4f;
	constexpr float sizeY = 0.05f;
	auto next = [&]() {
		ID += IDOffset;
		posY += offsetY;
	};

	// slider
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(posX, posY),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Planet Count:"
	));

	auto planetCount = std::make_shared<SliderAndInputLine>(
		ID,
		GetElementPosition(posX, posY + 0.04f),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		static_cast<int>(appContext.constants.world.minPlanetCount),
		static_cast<int>(appContext.constants.world.maxPlanetCount),
		static_cast<int>(appContext.constants.world.currentPlanetCount)
	);
	planetCount->SetActive(true, appContext);
	planetCount->SetOnSave([this](int value) {
		this->SetValue(value, SliderType::PLANET_COUNT);
		});
	m_elements.push_back(planetCount);
	m_slider.push_back(planetCount);

	next();

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(posX, posY),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Galaxy Width:"
	));

	auto galaxyWidth = std::make_shared<SliderAndInputLine>(
		ID,
		GetElementPosition(posX, posY + 0.04f),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		static_cast<int>(appContext.constants.world.minDimensionX),
		static_cast<int>(appContext.constants.world.maxDimensionX),
		static_cast<int>(appContext.constants.world.currentDimensionX)
	);
	galaxyWidth->SetActive(true, appContext);
	galaxyWidth->SetOnSave([this](int value) {
		this->SetValue(value, SliderType::DIMENSION_X);
		});
	m_elements.push_back(galaxyWidth);
	m_slider.push_back(galaxyWidth);

	next();

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(posX, posY),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Galaxy Height:"
	));

	auto galaxyHeight = std::make_shared<SliderAndInputLine>(
		ID,
		GetElementPosition(posX, posY + 0.04f),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		static_cast<int>(appContext.constants.world.minDimensionY),
		static_cast<int>(appContext.constants.world.maxDimensionY),
		static_cast<int>(appContext.constants.world.currentDimensionY)
	);
	galaxyHeight->SetActive(true, appContext);
	galaxyHeight->SetOnSave([this](int value) {
		this->SetValue(value, SliderType::DIMENSION_Y);
		});
	m_elements.push_back(galaxyHeight);
	m_slider.push_back(galaxyHeight);

	next();

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(posX, posY),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Fleet Speed:"
	));

	auto fleetSpeed = std::make_shared<SliderAndInputLine>(
		ID,
		GetElementPosition(posX, posY + 0.04f),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		static_cast<int>(appContext.constants.fleet.minFleetSpeed),
		static_cast<int>(appContext.constants.fleet.maxFleetSpeed),
		static_cast<int>(appContext.constants.fleet.currentFleetSpeed)
	);
	fleetSpeed->SetActive(true, appContext);
	fleetSpeed->SetOnSave([this](int value) {
		this->SetValue(value, SliderType::FLEET_SPEED);
		});
	m_elements.push_back(fleetSpeed);
	m_slider.push_back(fleetSpeed);

	next();

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(posX, posY),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"ca. Last Round:"
	));

	auto lastRound = std::make_shared<SliderAndInputLine>(
		ID,
		GetElementPosition(posX, posY + 0.04f),
		GetElementSize(sizeX, sizeY),
		Alignment::TOP_MID,
		resolution,
		static_cast<int>(appContext.constants.global.minRounds),
		static_cast<int>(appContext.constants.global.maxRounds),
		static_cast<int>(appContext.constants.global.currentTargetRound)
	);
	lastRound->SetActive(true, appContext);
	lastRound->SetOnSave([this](int value) {
		this->SetValue(value, SliderType::TARGET_ROUND);
		});
	m_elements.push_back(lastRound);
	m_slider.push_back(lastRound);

	// btn
	auto randomBtn = std::make_shared<ClassicButton>(
		1002,
		GetElementPosition(0.625f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		resolution,
		"Random",
		SoundType::CLICKED_RELEASE_STD
	);
	randomBtn->SetOnClick([this]() {
		this->SetRandom();
		});
	m_elements.push_back(randomBtn);

	auto backBtn = std::make_shared<ClassicButton>(
		1001,
		GetElementPosition(0.25f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		resolution,
		"Back",
		SoundType::CLICKED_RELEASE_STD
	);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::NEW_GAME_PLAYER)
		);
		});
	m_elements.push_back(backBtn);

	auto nextBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.85f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		resolution,
		"Next",
		SoundType::ACCEPTED
	);
	nextBtn->SetOnClick([]() {
		auto event = GenerateGalaxyEvent();
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(nextBtn);
}

void NewGameParameterScene::SetValue(int value, SliderType type) const {
	switch (type) {
	case SliderType::PLANET_COUNT:
		AppContext::GetInstance().constants.world.currentPlanetCount = value;
		return;
	case SliderType::DIMENSION_X:
		AppContext::GetInstance().constants.world.currentDimensionX = value;
		return;
	case SliderType::DIMENSION_Y:
		AppContext::GetInstance().constants.world.currentDimensionY = value;
		return;
	case SliderType::FLEET_SPEED:
		AppContext::GetInstance().constants.fleet.currentFleetSpeed = value;
		return;
	case SliderType::TARGET_ROUND:
		AppContext::GetInstance().constants.global.currentTargetRound = value;
		return;
	}
}

void NewGameParameterScene::SetRandom() const {
	m_eventSettings->SetRandom();
	for (auto& s : m_slider) {
		s->RandomValue();
	}
}

void NewGameParameterScene::NextScene() const {
	SwitchSceneEvent event{ SceneType::VALIDATE_GALAXY };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

NewGameParameterScene::NewGameParameterScene(Vector2 resolution)
	: Scene{ { 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution } {
	Initialize(resolution);
	AppContext::GetInstance().eventManager.AddListener(this);
}

NewGameParameterScene::~NewGameParameterScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void NewGameParameterScene::OnEvent(Event const& event) {

	if (auto const* GalaxyEvent = dynamic_cast<GalaxyGeneratedUIEvent const*>(&event)) {
		NextScene();
		return;
	}
}
