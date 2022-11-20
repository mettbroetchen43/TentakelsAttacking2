//
// Purpur Tentakel
// 20.11.2022
//

#include "ValidateGalaxy.h"
#include "GenerelEvents.hpp"
#include "SceneType.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "GalaxyAndSlider.h"
#include "Text.h"

void ValidateGalaxyScene::Initialize() {

	auto text = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.01f),
		GetElementSize(0.4f, 0.07f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.07f,
		"Validate your galaxy:"
		);
	m_elements.push_back(text);

	auto backBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.1f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"Back",
		SoundType::CLICKED_RELEASE_STD
		);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::NEW_GAME_PARAMETER));
		});
	m_elements.push_back(backBtn);

	auto reGenerateBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(0.5f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		"Regenerate",
		SoundType::CLICKED_RELEASE_STD
		);
	reGenerateBtn->SetOnClick([this]() {
		this->NewGalaxy();
		});
	m_elements.push_back(reGenerateBtn);

	auto nextBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.9f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"Next",
		SoundType::ACCEPTED
		);
	nextBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::MAIN_MENU));
		});
	m_elements.push_back(nextBtn);
}

void ValidateGalaxyScene::InitializeGalaxy(SendGalaxyPointerEvent const*)
{
}

void ValidateGalaxyScene::NewGalaxy()
{
}

ValidateGalaxyScene::ValidateGalaxyScene(Vector2 resolution)
	: Scene({0.0f,0.0f}, {1.0f,1.0f}, Alignment::DEFAULT, resolution) {
	
	AppContext& appContext = AppContext::GetInstance();

	appContext.eventManager.AddListener(this);

	Initialize();

	auto event = GetGalaxyPointerEvent();
	appContext.eventManager.InvokeEvent(event);
}
ValidateGalaxyScene::~ValidateGalaxyScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void ValidateGalaxyScene::OnEvent(Event const& event) {

	if (auto const* GalaxyEvent = dynamic_cast<SendGalaxyPointerEvent const*>(&event)) {
		InitializeGalaxy(GalaxyEvent);
		return;
	}
}
