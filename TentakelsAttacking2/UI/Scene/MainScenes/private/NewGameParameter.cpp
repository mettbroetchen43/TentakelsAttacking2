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
#include "SceneType.hpp"
#include "GameEventSettings.h"
#include "SliderAndInputLine.h"

void NewGameParameterScene::Initialize(Vector2 resolution) {
	AppContext& appContext = AppContext::GetInstance();

	// title
	m_elements.push_back(std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		false,
		resolution,
		appContext
		));

	// parameters
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.5f, 0.2f),
		GetElementSize(0.3f, 0.1f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.07f,
		"Parameter",
		resolution
		));

	// line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.5f,0.3f),
		GetElementSize(0.0f,0.65f),
		Alignment::TOP_MID,
		2.0f,
		resolution
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

	// slider
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.75f, 0.3f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		Alignment::TOP_LEFT,
		0.04f,
		"Planet Count:",
		resolution
		));

	auto planetCount = std::make_shared<SliderAndInputLine>(
		100,
		GetElementPosition(0.75f, 0.34f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		static_cast<int>(appContext.constants.world.minPlanetCount),
		static_cast<int>(appContext.constants.world.maxPlanetCount),
		static_cast<int>(appContext.constants.world.currentPlanetCount),
		resolution
		);
	planetCount->SetActive(true,appContext);
	planetCount->SetOnSave([this](int value) {
		this->SetValue(value, 0);
		});
	m_elements.push_back(planetCount);
	m_slider.push_back(planetCount);

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.75f, 0.4f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		Alignment::TOP_LEFT,
		0.04f,
		"Galaxy Width:",
		resolution
		));

	auto galaxyWidth = std::make_shared<SliderAndInputLine>(
		200,
		GetElementPosition(0.75f, 0.44f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		static_cast<int>(appContext.constants.world.minDiemnsionX),
		static_cast<int>(appContext.constants.world.maxDiemnsionX),
		static_cast<int>(appContext.constants.world.currentDimensionX),
		resolution
		);
	galaxyWidth->SetActive(true, appContext);
	galaxyWidth->SetOnSave([this](int value) {
		this->SetValue(value, 1);
		});
	m_elements.push_back(galaxyWidth);
	m_slider.push_back(galaxyWidth);

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.75f, 0.5f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		Alignment::TOP_LEFT,
		0.04f,
		"Galaxy Height:",
		resolution
		));

	auto galaxyHeight = std::make_shared<SliderAndInputLine>(
		300,
		GetElementPosition(0.75f, 0.54f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		static_cast<int>(appContext.constants.world.minDiemnsionY),
		static_cast<int>(appContext.constants.world.maxDiemnsionY),
		static_cast<int>(appContext.constants.world.currentDimensionY),
		resolution
		);
	galaxyHeight->SetActive(true, appContext);
	galaxyHeight->SetOnSave([this](int value) {
		this->SetValue(value, 2);
		});
	m_elements.push_back(galaxyHeight);
	m_slider.push_back(galaxyHeight);

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.75f, 0.6f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		Alignment::TOP_LEFT,
		0.04f,
		"ca. Last Round:",
		resolution
		));

	auto lastRound = std::make_shared<SliderAndInputLine>(
		400,
		GetElementPosition(0.75f, 0.64f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		static_cast<int>(appContext.constants.global.minRounds),
		static_cast<int>(appContext.constants.global.maxRounds),
		static_cast<int>(appContext.constants.global.currentRounds),
		resolution
		);
	lastRound->SetActive(true, appContext);
	lastRound->SetOnSave([this](int value) {
		this->SetValue(value, 3);
		});
	m_elements.push_back(lastRound);
	m_slider.push_back(lastRound);

	// btn
	auto randomBtn = std::make_shared<ClassicButton>(
		1002,
		GetElementPosition(0.25f, 0.95f),
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
		GetElementPosition(0.625f, 0.95f),
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

	auto startBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.85f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		resolution,
		"Start",
		SoundType::ACCEPTED
		);
	m_elements.push_back(startBtn);
}

void NewGameParameterScene::SetValue(int value, int ID) const {
	switch (ID) {
		case 0:
			AppContext::GetInstance().constants.world.currentPlanetCount = value;
			return;
		case 1:
			AppContext::GetInstance().constants.world.currentDimensionX = value;
			return;
		case 2:
			AppContext::GetInstance().constants.world.currentDimensionY = value;
			return;
		case 3:
			AppContext::GetInstance().constants.global.currentRounds = value;
			return;
	}
}

void NewGameParameterScene::SetRandom() const {
	m_eventSettings->SetRandom();
	for (auto& s : m_slider) {
		s->RandomValue();
	}
}

NewGameParameterScene::NewGameParameterScene(Vector2 resolution)
	: Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT) {
	Initialize(resolution);
}
