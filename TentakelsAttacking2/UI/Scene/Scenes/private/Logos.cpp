//
// Purpur Tentakel
// 14.09.2022
//

#include "Logos.h"
#include "SceneType.hpp"
#include "AppContext.h"
#include "UIManager.h"
#include "Text.h"
#include "Picture.h"
#include "HInput.h"
#include <memory>


void LogoScene::Initialize(Vector2 resolution) {
	auto logo = std::make_shared<Picture>(
		GetElementPosition(0.5f, 0.1f),
		GetElementSize(0.0f, 0.5f),
		Alignment::TOP_MID,
		AssetType::LOGO,
		resolution
		);
	m_elements.push_back(logo);

	auto mainText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.65f),
		GetElementSize(0.45f, 0.1f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.07f,
		"A Purpur Tentakel production",
		resolution
		);
	m_elements.push_back(mainText);

	auto skipText = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.98f),
		GetElementSize(0.11f, 0.03f),
		Alignment::BOTTOM_RIGHT,
		Alignment::BOTTOM_RIGHT,
		0.03f,
		"skip with [ESC]",
		resolution
		);
	m_elements.push_back(skipText);
}

LogoScene::LogoScene(Vector2 pos, Vector2 size, Alignment alignment,
	SceneType nextScene, Vector2 resolution)
	:Scene(pos, size, alignment), m_nextScene(nextScene), m_time(GetTime()) {
	Initialize(resolution);
}
void LogoScene::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	bool nextScene =
		IsBackInputPressed()
		or (m_time + SCENE_LENGTH) < GetTime();
	if (nextScene) {
		auto event = SwitchSceneEvent(m_nextScene);
		appContext.eventManager.InvokeEvent(event);
	}

	for (auto e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}
void LogoScene::Render(AppContext const& appContext) {
	for (auto e : m_elements) {
		e->Render(appContext);
	}
}
void LogoScene::Resize(Vector2 resolution, AppContext const& appContext){
	for (auto e : m_elements) {
		e->Resize(resolution, appContext);
	}
}

void LogoScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
