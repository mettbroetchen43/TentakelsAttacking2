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
	auto gameEvents = std::make_shared<GameEventSettings>(
		1,
		GetElementPosition(0.25f, 0.3f),
		GetElementSize(0.25f, 0.5f),
		Alignment::TOP_MID,
		resolution
		);
	gameEvents->SetActive(true, appContext);
	m_elements.push_back(gameEvents);

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
		appContext.constants.world.minPlanetCount,
		appContext.constants.world.maxPlanetCount,
		appContext.constants.world.currentPlanetCount,
		resolution
		);
	planetCount->SetActive(true,appContext);
	m_elements.push_back(planetCount);

	// btn
	auto randomBtn = std::make_shared<ClassicButton>(
		1003,
		GetElementPosition(0.15f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		resolution,
		"Random",
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(randomBtn);

	auto resetBtn = std::make_shared<ClassicButton>(
		1002,
		GetElementPosition(0.375f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		resolution,
		"Reset",
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(resetBtn);

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

NewGameParameterScene::NewGameParameterScene(Vector2 resolution)
	: Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT) {
	Initialize(resolution);
}
