//
// Purpur Tentakel
// 05.09.2022
//

#include "SceneManager.h"
#include "Scene.h"
#include "SceneType.h"
#include "MessagePopUp.h"
#include "UIManager.h"
#include "Scenes.hpp"
#include "AppContext.h"
#include "HPrint.h"
#include <CustomRaylib.h>


void SceneManager::InitializeNewScene(SceneType sceneType) {
	switch (sceneType) {
		case SceneType::TEST:
			m_currentScene = std::make_shared<TestScene>(
				m_uiManager->GetResolution( ));
			return;
		case SceneType::LOGO:
			m_currentScene= std::make_shared<LogoScene>(
				m_uiManager->GetResolution());
			return;
		case SceneType::INTRO:
			m_currentScene = std::make_shared<Intro>(
				m_uiManager->GetResolution());
			return;
		case SceneType::MAIN_MENU:
			m_currentScene = std::make_shared<MainMenu>(
				m_uiManager->GetResolution());
			return;
		case SceneType::NEW_GAME_PLAYER:
			m_currentScene = std::make_shared<NewGamePlayerScene>(
				m_uiManager->GetResolution());
			return;
		case SceneType::NEW_GAME_PARAMETER:
			m_currentScene = std::make_shared<NewGameParameterScene>(
				m_uiManager->GetResolution());
			return;
		case SceneType::VALIDATE_GALAXY:
			m_currentScene = std::make_shared<ValidateGalaxyScene>(
				m_uiManager->GetResolution());
			return;
		case SceneType::MAIN:
			m_currentScene = std::make_shared<MainScene>(
				m_uiManager->GetResolution());
			return;
		case SceneType::SETTINGS:
			m_currentScene = std::make_shared<SettingsScene>(
				m_uiManager->GetResolution(), GetContinueSceneType());
			return;
		case SceneType::CREDITS:
			m_currentScene = std::make_shared<CreditsScene>(
				m_uiManager->GetResolution());
			return;
		case SceneType::UPDATE_EVALUATION:
			m_currentScene = std::make_shared<UpdateEvaluationScene>(
				m_uiManager->GetResolution());
			return;
	}
}

void SceneManager::SwitchScene(AppContext_ty_c appContext) {

	if (m_currentSceneType == m_nextSceneType) {
		return;
	}

	if (!m_first) {
		ClearFocusEvent event;
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		m_first = true;
	}

	NewFocusLayerEvent event;
	appContext.eventManager.InvokeEvent(event);

	InitializeNewScene(m_nextSceneType);

	m_currentScene->SetActive(true, appContext);
	m_currentSceneType = m_nextSceneType;

	Print("Scene switched to " + GetStringBySceneType(m_currentSceneType), PrintType::INFO);
}

SceneType SceneManager::GetContinueSceneType() const {
	
	switch (m_currentSceneType) {
		case SceneType::MAIN:
			return SceneType::MAIN;
		default:
			return SceneType::NONE;
	}
}

SceneManager::SceneManager(UIManager* uiManager)
	: m_uiManager{ uiManager }, m_popUpManager{ uiManager->GetResolution() } {
	AppContext::GetInstance().eventManager.AddListener(this);
	Print("SceneManager", PrintType::INITIALIZE);
}

void SceneManager::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	SwitchScene(appContext);

	if (!m_popUpManager.IsActivePopUp()){
		m_currentScene->CheckAndUpdate(mousePosition, appContext);
	}
	m_popUpManager.CheckAndUpdate(mousePosition, appContext);
}
void SceneManager::Render(AppContext_ty_c appContext) {
	m_currentScene->Render(appContext);
	m_popUpManager.Render(appContext);
}
void SceneManager::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	m_currentScene->Resize(resolution, appContext);

	m_popUpManager.Resize(resolution, appContext);
}

void SceneManager::SetResolution(Vector2 resolution) {
	m_popUpManager.Resize(resolution, AppContext::GetInstance());
}

void SceneManager::OnEvent(Event const& event) {

	if (auto const SceneEvent = dynamic_cast<SwitchSceneEvent const*>(&event)) {
		m_nextSceneType = SceneEvent->GetSceneType();
		return;
	}
}
