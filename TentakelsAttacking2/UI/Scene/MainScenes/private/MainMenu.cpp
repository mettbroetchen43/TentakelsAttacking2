//
// Purpur Tentakel
// 19.09.2022
//

#include "MainMenu.h"
#include "AppContext.h"
#include "UIManager.h"
#include "ClassicButton.h"
#include "GalaxyAndSlider.h"
#include "Title.h"
#include "Text.h"
#include <memory>

void MainMenu::Initialize(Vector2 resolution, AppContext_ty appContext) {
	float const btnPosX{ 0.23f };
	float       btnPosY{ 0.115f };
	float const btnSizX{ 0.2f };
	float const btnSizY{ 0.1f };
	float const btnOffset{ 0.13f };
	int         focusID{ 1 };

	auto newGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_new_game_btn"),
		SoundType::ACCEPTED
		);
	newGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::NEW_GAME_PLAYER));
		});
	m_elements.push_back(newGameBtn);

	btnPosY += btnOffset;
	++focusID;

	auto continueBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_continue_btn"),
		SoundType::ACCEPTED
	);
	continueBtn->SetEnabled(appContext.constants.global.isGameRunning);
	continueBtn->SetOnClick([]() {
			ResumeGameEvent const event{ };
			AppContext::GetInstance().eventManager.InvokeEvent(event);
		}
	);

	m_elements.push_back(continueBtn);

	appContext.eventManager.InvokeEvent(GetGalaxyPointerEvent{ });

	btnPosY += btnOffset;
	++focusID;

	auto saveGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_save_btn"),
		SoundType::ACCEPTED
	);
	saveGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::TEST)
		);
		}
	);
	saveGameBtn->SetEnabled(false);
	m_elements.push_back(saveGameBtn);

	btnPosY += btnOffset;
	++focusID;

	auto loadGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_load_btn"),
		SoundType::ACCEPTED
		);
	loadGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::TEST)
			);
		}
	);
	loadGameBtn->SetEnabled(false);
	m_elements.push_back(loadGameBtn);

	btnPosY += btnOffset;
	++focusID;

	auto settingsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_settings_btn"),
		SoundType::CLICKED_RELEASE_STD
		);
	settingsBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::SETTINGS)
			);
		}
	);
	m_elements.push_back(settingsBtn);

	btnPosY += btnOffset;
	++focusID;

	auto creditsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_credits_btn"),
		SoundType::CLICKED_RELEASE_STD
		);
	creditsBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::CREDITS)
		);
		}
	);
	m_elements.push_back(creditsBtn);

	btnPosY += btnOffset;
	++focusID;

	auto quitBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_quit_btn"),
		SoundType::ACCEPTED
		);
	quitBtn->SetOnClick([]() {AppContext::GetInstance().eventManager.InvokeEvent(CloseWindowEvent());});
	m_elements.push_back(quitBtn);

	auto galaxy = std::make_shared<GalaxyScene>(
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.7f, 0.7f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		true,
		false
		);
	galaxy->SetActive(true, appContext);
	galaxy->SetIsScaling(false);
	galaxy->SetIsEnabled(false);
	m_elements.push_back(galaxy);

	auto title = std::make_shared<Title>(
		GetElementPosition(0.625f, 0.025f),
		GetElementSize(0.7f, 0.2f),
		Alignment::TOP_MID,
		resolution,
		false,
		appContext
		);
	m_elements.push_back(title);

	auto versionAndCopyRight = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.98f),
		GetElementSize(0.1f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		Alignment::BOTTOM_RIGHT,
		0.02f,
		appContext.constants.global.gameVersion + '\n' 
			+ appContext.constants.global.copyRight
		);
	m_elements.push_back(versionAndCopyRight);
}

MainMenu::MainMenu(Vector2 resolution)
	: Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, Alignment::DEFAULT, resolution } {

	AppContext_ty appContext{ AppContext::GetInstance() };

	Initialize(resolution, appContext);
}

