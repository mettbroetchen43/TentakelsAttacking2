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
	Window_ty_c window{ AppContext::GetInstance().constants.window };
	switch (sceneType) {
		case SceneType::TEST:
			m_currentScene = std::make_shared<TestScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::LOGO:
			m_currentScene= std::make_shared<LogoScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::INTRO:
			m_currentScene = std::make_shared<Intro>(
				window.currentResolutionVec
			);
			return;

		case SceneType::MAIN_MENU:
			m_currentScene = std::make_shared<MainMenu>(
				window.currentResolutionVec
			);
			return;

		case SceneType::NEW_GAME_PLAYER:
			m_currentScene = std::make_shared<NewGamePlayerScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::NEW_GAME_PARAMETER:
			m_currentScene = std::make_shared<NewGameParameterScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::VALIDATE_GALAXY:
			m_currentScene = std::make_shared<ValidateGalaxyScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::MAIN:
			m_currentScene = std::make_shared<MainScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::GAME_SETTINGS:
			m_currentScene = std::make_shared<GameSettingsScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::APP_SETTINGS:
			m_currentScene = std::make_shared<AppSettingsScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::CREDITS:
			m_currentScene = std::make_shared<CreditsScene>(
				window.currentResolutionVec
			);
			return;

		case SceneType::UPDATE_EVALUATION:
			m_currentScene = std::make_shared<UpdateEvaluationScene>(
				window.currentResolutionVec
			);
			return;
	}
}

void SceneManager::SwitchScene(AppContext_ty_c appContext) {

	if (m_currentSceneType == m_nextSceneType) {
		return;
	}

	ClearFocusEvent const closeEvent;
	appContext.eventManager.InvokeEvent(closeEvent);

	NewFocusLayerEvent const newLayerEvent;
	appContext.eventManager.InvokeEvent(newLayerEvent);

	InitializeNewScene(m_nextSceneType);

	m_currentScene->SetActive(true, appContext);
	m_currentSceneType = m_nextSceneType;

	Print(
		PrintType::INFO,
		"scene switched to -> {}",
		GetStringBySceneType(m_currentSceneType)
	);
}

SceneManager::SceneManager(UIManager* uiManager)
	: m_uiManager{ uiManager }, m_popUpManager{ AppContext::GetInstance().constants.window.currentResolutionVec } {
	AppContext::GetInstance().eventManager.AddListener(this);
	Print(PrintType::INITIALIZE, "SceneManager");
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

bool SceneManager::IsValidCurrentScene() const {
	return m_currentScene != nullptr;
}
