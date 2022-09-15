//
// Purpur Tentakel
// 14.09.2022
//

#include "Logos.h"
#include "SceneType.h"
#include "AppContext.h"
#include "AssetType.h"
#include "UIManager.h"
#include <memory>


void LogoScene::Initialize(UIManager const& uiManager) {
	auto mainText = std::make_shared<Text>(
		GetElementPosition(0.35f, 0.5f),
		GetElementSize(0.35f, 0.05f),
		0.07f,
		"A Purpur Tentakel production",
		uiManager.GetResolution()
		);
	mainText->RenderRectangle(true);
	m_elements.push_back(mainText);

	auto skipText = std::make_shared<Text>(
		GetElementPosition(0.89f, 0.95f),
		GetElementSize(0.11f, 0.03f),
		0.03f,
		"skip with [ESC]",
		uiManager.GetResolution()
		);
	skipText->RenderRectangle(true);
	m_elements.push_back(skipText);
}

LogoScene::LogoScene(Vector2 pos, Vector2 size,SceneType nextScene, UIManager const& uiManager)
	:Scene(pos, size), m_nextScene(nextScene), m_time(GetTime()) {
	m_logo = AppContext::GetInstance().assetManager.GetTexture(AssetType::LOGO);
	Initialize(uiManager);
}
void LogoScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	bool nextScene =
		IsKeyPressed(KEY_ESCAPE)
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
