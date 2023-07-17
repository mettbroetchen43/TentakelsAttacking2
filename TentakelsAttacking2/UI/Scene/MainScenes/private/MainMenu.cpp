//
// Purpur Tentakel
// 19.09.2022
//

#include "MainMenu.h"
#include "AppContext.h"
#include "UIManager.h"
#include "ClassicButton.h"
#include "ExpandingButton.h"
#include "GalaxyAndSlider.h"
#include "Title.h"
#include "Text.h"
#include <memory>

void MainMenu::Initialize(Vector2 resolution, AppContext_ty appContext) {

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



	float constexpr btnPosX{ 0.23f };
	float           btnPosY{ 0.115f };
	float constexpr btnSizX{ 0.2f };
	float constexpr btnSizY{ 0.1f };
	float constexpr btnOffset{ 0.13f };
	int             focusID{ 1 };

	auto const incFID{[&](){
		++focusID;
	}};
	auto const incAll{[&](){
		btnPosY += btnOffset;
		incFID();
	}};

	auto gameBtn = std::make_shared<ExpandingButton>(
		focusID,
		GetElementPosition(btnPosX,btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		m_resolution,
		ExpandingButton::RIGHT,
		0.005f,
		10.0f,
		"game"
	);
	m_elements.push_back(gameBtn);

	incFID();

	auto continueBtn = std::make_shared<ClassicButton>(
		focusID,
		Vector2{ 0.0f,0.0f },
		Vector2{ 0.0f,0.0f },
		Alignment::DEFAULT,
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
	gameBtn->Add(continueBtn, appContext.constants.global.isGameRunning);

	incFID();

	auto newGameBtn = std::make_shared<ClassicButton>(
		focusID,
		Vector2{ 0.0f,0.0f },
		Vector2{ 0.0f,0.0f },
		Alignment::DEFAULT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_new_game_btn"),
		SoundType::ACCEPTED
	);
	newGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::NEW_GAME_PLAYER));
		});
	gameBtn->Add(newGameBtn, true);

	incFID();

	auto networkBtn = std::make_shared<ClassicButton>(
		focusID,
		Vector2{ 0.0f,0.0f },
		Vector2{ 0.0f,0.0f },
		Alignment::DEFAULT,
		resolution,
		"network",
		SoundType::ACCEPTED
	);
	gameBtn->Add(networkBtn, false);
	gameBtn->Update();

	incAll();

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
			AppContext_ty appContext{ AppContext::GetInstance() };
			if (not appContext.constants.global.isGameSaved) {
				appContext.constants.global.isGameSaved = true;
				ShowMessagePopUpEvent const event {
					"debug save",
					"set save bool to false\nwill be set later when a game was saved.",
					[]() {}
				};
				appContext.eventManager.InvokeEvent(event);
			}
		}
	);
	m_elements.push_back(saveGameBtn);

	incAll();

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
			AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::TEST));
		}
	);
	loadGameBtn->SetEnabled(false);
	m_elements.push_back(loadGameBtn);

	incAll();

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

	incAll();

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

	incAll();

	auto quitBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		appContext.languageManager.Text("scene_main_menu_quit_btn"),
		SoundType::ACCEPTED
	);
	quitBtn->SetOnClick(
		[]() {
			AppContext::GetInstance().eventManager.InvokeEvent(QuitGameEvent{ });
		}
	);
	m_elements.push_back(quitBtn);


}

MainMenu::MainMenu(Vector2 resolution)
	: Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, Alignment::DEFAULT, resolution } {

	AppContext_ty appContext{ AppContext::GetInstance() };

	Initialize(resolution, appContext);
}
