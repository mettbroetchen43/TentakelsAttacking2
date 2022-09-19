//
// Purpur Tentakel
// 19.09.2022
//

#include "MainMenu.h"
#include "AppContext.h"
#include "UIManager.h"
#include "AssetType.h"
#include "SoundType.h"
#include "ClassicButton.h"
#include <memory>

void MainMenu::Initialize(UIManager const& uiManager, AppContext& appContext) {
	float btnX = 0.05f;

	auto newGameBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(btnX, 0.3f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_LEFT,
		uiManager.GetResolution(),
		"New Game",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	m_elements.push_back(newGameBtn);

	auto loadGameBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(btnX, 0.45f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_LEFT,
		uiManager.GetResolution(),
		"Load Game",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	m_elements.push_back(loadGameBtn);

	auto SettingsBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(btnX, 0.6f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_LEFT,
		uiManager.GetResolution(),
		"Settings",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(SettingsBtn);

	auto CreditsBtn = std::make_shared<ClassicButton>(
		4,
		GetElementPosition(btnX, 0.75f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_LEFT,
		uiManager.GetResolution(),
		"Credits",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(CreditsBtn);

	auto QuitBtn = std::make_shared<ClassicButton>(
		5,
		GetElementPosition(btnX, 0.9f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_LEFT,
		uiManager.GetResolution(),
		"Quit",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	m_elements.push_back(QuitBtn);
}

MainMenu::MainMenu(Vector2 pos, Vector2 size, Alignment alignment, UIManager const& uiManager)
	: Scene(pos, size, alignment) {

	AppContext& appContext = AppContext::GetInstance();
	Initialize(uiManager, appContext);
}

void MainMenu::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
