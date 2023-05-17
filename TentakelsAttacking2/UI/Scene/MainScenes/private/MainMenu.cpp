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
#include <iostream>

void MainMenu::Initialize(Vector2 resolution, AppContext& appContext) {
	float btnPosX = 0.23f;
	float btnPosY = 0.115f;
	float btnSizX = 0.2f;
	float btnSizY = 0.1f;
	float btnOffset = 0.13f;
	int focusID;

	auto newGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"New Game",
		SoundType::ACCEPTED
		);
	newGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::NEW_GAME_PLAYER));
		});
	m_elements.push_back(newGameBtn);

	btnPosY += btnOffset;
	++focusID;

	m_continueBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"continue",
		SoundType::ACCEPTED
	);
	m_continueBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::MAIN));
		});
	m_elements.push_back(m_continueBtn);

	appContext.eventManager.InvokeEvent(GetGalaxyPointerEvent());

	btnPosY += btnOffset;
	++focusID;

	auto saveGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Save Game",
		SoundType::ACCEPTED
	);
	saveGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::TEST)
		);
		}
	);
	saveGameBtn->SetEnabled(false);// TODO: need to implement save system
	m_elements.push_back(saveGameBtn);

	btnPosY += btnOffset;
	++focusID;

	auto loadGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Load Game",
		SoundType::ACCEPTED
		);
	loadGameBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::TEST)
			);
		}
	);
	loadGameBtn->SetEnabled(false); // TODO: need to implement load system
	m_elements.push_back(loadGameBtn);

	btnPosY += btnOffset;
	++focusID;

	auto settingsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		resolution,
		"Settings",
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
		"Credits",
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
		"Quit",
		SoundType::ACCEPTED
		);
	quitBtn->SetOnClick([]() {AppContext::GetInstance().eventManager.InvokeEvent(CloseWindowEvent());});
	m_elements.push_back(quitBtn);

	auto galaxy = std::make_shared<GalaxyScene>(
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.7f, 0.7f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		true
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
		appContext.constants.global.version + '\n' 
			+ appContext.constants.global.copyRight
		);
	m_elements.push_back(versionAndCopyRight);
}

MainMenu::MainMenu(Vector2 resolution)
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT, resolution) {

	AppContext& appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);

	Initialize(resolution, appContext);
}

MainMenu::~MainMenu() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void MainMenu::OnEvent(Event const& event) {
	if (auto const* galaxyEvent = dynamic_cast<SendGalaxyPointerEvent const*>(&event)) {
		if (galaxyEvent->IsShowGalaxy()) { return; }

		if (galaxyEvent->GetGalaxy() == nullptr) {
			m_continueBtn->SetEnabled(false);
		}
		else {
			m_continueBtn->SetEnabled(true);
		}
		std::cout << "Galaxy Event \n";
	}
}
