//
// Purpur Tentakel
// 01.11.2022
//

#include "Settings.h"
#include "Title.h"
#include "ClassicButton.h"
#include "SceneType.h"
#include "Line.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"

void SettingsScene::Initialize() {
	AppContext_ty appContext{ AppContext::GetInstance() };

	// title
	m_elements.push_back(std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		m_resolution,
		false,
		appContext
		));

	// line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.5f, 0.3f),
		GetElementPosition(0.5f, 0.95f),
		m_resolution,
		2.0f,
		WHITE
	));

	// btn
	auto continueBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.75f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		appContext.languageManager.Text("scene_settings_continue_btn"),
		SoundType::ACCEPTED
	);
	continueBtn->SetEnabled(appContext.constants.global.isGameRunning); 
	continueBtn->SetOnClick([]() {
			ResumeGameEvent const event{ };
			AppContext::GetInstance().eventManager.InvokeEvent(event);
		}
	);
	m_elements.push_back(continueBtn);

	auto backBtn = std::make_shared<ClassicButton>(
		1001,
		GetElementPosition(0.25f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		appContext.languageManager.Text("scene_settings_main_menu_btn"),
		SoundType::CLICKED_RELEASE_STD
		);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent{ SceneType::MAIN_MENU }
		);
		}
	);
	m_elements.push_back(backBtn);
}

SettingsScene::SettingsScene(Vector2 resolution)
	:Scene{ { 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution } {
	Initialize();
}

void SettingsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}
void SettingsScene::Render(AppContext_ty_c appContext) {
	Scene::Render(appContext);
}
void SettingsScene::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	Scene::Resize(resolution, appContext);
}
