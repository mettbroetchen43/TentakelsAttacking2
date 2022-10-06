//
// Purpur Tentakel
// 05.09.2022
//

#include "SceneManager.h"
#include "Scene.h"
#include "PopUp.h"
#include "MessagePopUp.h"
#include "Scenes.h"
#include "UIManager.h"
#include "AppContext.h"
#include <raylib.h>

void SceneManager::InitializeScenes() {
	auto test = std::make_shared<TestScene>(
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Alignment::DEFAULT,
		*m_uiManager);
	m_scenes[SceneType::TEST] = test;

	auto logo = std::make_shared<LogoScene>(
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Alignment::DEFAULT,
		SceneType::INTRO,
		*m_uiManager);
	m_scenes[SceneType::LOGO] = logo;

	auto intro = std::make_shared<Intro>(
		Vector2(0.0f,0.0f),
		Vector2(1.0f,1.0f),
		Alignment::DEFAULT,
		*m_uiManager,
		SceneType::MAIN_MENU);
	m_scenes[SceneType::INTRO] = intro;

	auto mainMenu = std::make_shared<MainMenu>(
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Alignment::DEFAULT,
		*m_uiManager
		);
	m_scenes[SceneType::MAIN_MENU] = mainMenu;
}

void SceneManager::NewMessagePopUp(std::string const& title, std::string const& subTitle) {
	AppContext& appContext = AppContext::GetInstance();
	auto event = NewFocusLayerEvent();
	appContext.eventManager.InvokeEvent(event);

	m_popUp.push_back(std::make_shared<MessagePopUp>(
		Vector2(0.4f, 0.4f),
		Vector2(0.3f, 0.3f),
		Alignment::DEFAULT,
		m_uiManager->GetResolution(),
		title,
		subTitle,
		AssetType::BUTTON_DEFAULT,
		AssetType::EXCLAMATION_MARK
	));
}
void SceneManager::DeleteLastPopUp() {
	AppContext& appContext = AppContext::GetInstance();
	auto event = DeleteFocusLayerEvent();
	appContext.eventManager.InvokeEvent(event);

	if (m_popUp.size() > 0) {
		m_popUp.pop_back();
	}
}

SceneManager::SceneManager(UIManager* uiManager)
	: m_uiManager(uiManager){
	InitializeScenes();
	AppContext& appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);
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

void SceneManager::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (m_popUp.size() == 0){
		m_currentScene->CheckAndUpdate(mousePosition, appContext);
	}
	for (auto p : m_popUp) {
		p->CheckAndUpdate(mousePosition, appContext);
	}
}
void SceneManager::Render(AppContext const& appContext) {
	m_currentScene->Render(appContext);
	for (auto p : m_popUp) {
		p->Render(appContext);
	}
}
void SceneManager::Resize(Vector2 resolution, AppContext const& appContext) {
	for (auto [sceneType, scene] : m_scenes) {
		scene->Resize(resolution, appContext);
	}

	for (auto p : m_popUp) {
		p->Resize(resolution, appContext);
	}
}

void SceneManager::OnEvent(Event const& event) {

	if (auto const PopUpEvent = dynamic_cast<ShowMessagePopUpEvent const*>(&event)) {
		NewMessagePopUp(PopUpEvent->GetTitle(), PopUpEvent->GetSubTitle());
		return;
	}
	if (auto const PopUpEvent = dynamic_cast<ClosePopUpEvent const*>(&event)) {
		DeleteLastPopUp();
		return;
	}
	if (auto const SceneEvent = dynamic_cast<SwitchSceneEvent const*>(&event)) {
		SwitchScene(SceneEvent->GetSceneType(), AppContext::GetInstance());
		return;
	}
}
