//
// Purpur Tentakel
// 05.09.2022
//

#include "SceneManager.h"
#include "Scene.h"
#include "MessagePopUp.h"
#include "UIManager.h"
#include "Scenes.hpp"
#include "AppContext.h"
#include <raylib.h>

/*
	switch (nextScene){
		case SceneType::TestScene 
			m_currentScene = std::make_shared<TestScene>(resolution);
			break;
	}
*/

void SceneManager::InitializeScenes() {
	auto test = std::make_shared<TestScene>(
		m_uiManager->GetResolution()
		);
	m_scenes[SceneType::TEST] = test;

	auto logo = std::make_shared<LogoScene>(
		m_uiManager->GetResolution()
		);
	m_scenes[SceneType::LOGO] = logo;

	auto intro = std::make_shared<Intro>(
		m_uiManager->GetResolution()
		);
	m_scenes[SceneType::INTRO] = intro;

	auto mainMenu = std::make_shared<MainMenu>(
		m_uiManager->GetResolution()
		);
	m_scenes[SceneType::MAIN_MENU] = mainMenu;

	auto newGamePlayer = std::make_shared<NewGamePlayerScene>(
		m_uiManager->GetResolution()
		);
	m_scenes[SceneType::NEW_GAME_PLAYER] = newGamePlayer;
}

SceneManager::SceneManager(UIManager* uiManager)
	: m_uiManager(uiManager), m_popUpManager(uiManager->GetResolution()) {
	InitializeScenes();
	AppContext::GetInstance().eventManager.AddListener(this);
}

void SceneManager::SwitchScene(SceneType sceneType, AppContext const& appCpntext) {
	if (m_currentScene) {
		auto event = ClearFocusEvent();
		appCpntext.eventManager.InvokeEvent(event);

		m_currentScene->SetActive(false, appCpntext);
	}
	m_currentScene = m_scenes.at(sceneType);

	auto event = NewFocusLayerEvent();
	appCpntext.eventManager.InvokeEvent(event);

	m_currentScene->SetActive(true, appCpntext);
}

void SceneManager::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	if (!m_popUpManager.IsActivePopUp()){
		m_currentScene->CheckAndUpdate(mousePosition, appContext);
	}
	m_popUpManager.CheckAndUpdate(mousePosition, appContext);
}
void SceneManager::Render(AppContext const& appContext) {
	m_currentScene->Render(appContext);
	m_popUpManager.Render(appContext);
}
void SceneManager::Resize(Vector2 resolution, AppContext const& appContext) {
	for (auto [sceneType, scene] : m_scenes) {
		scene->Resize(resolution, appContext);
	}

	m_popUpManager.Resize(resolution, appContext);
}

void SceneManager::OnEvent(Event const& event) {

	if (auto const SceneEvent = dynamic_cast<SwitchSceneEvent const*>(&event)) {
		SwitchScene(SceneEvent->GetSceneType(), AppContext::GetInstance());
		return;
	}
}
