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
#include "Title.h"
#include "Text.h"
#include "UIEvents.h"
#include <memory>

void MainMenu::Initialize(UIManager const& uiManager, AppContext& appContext) {
	float btnPosX = 0.25f;
	float btnPosY = 0.3f;
	float btnSizX = 0.2f;
	float btnSizY = 0.1f;
	int focusID;

	auto newGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		uiManager.GetResolution(),
		"New Game",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	newGameBtn->SetEnabled(false);
	m_elements.push_back(newGameBtn);

	btnPosY += 0.15f;
	++focusID;

	auto loadGameBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		uiManager.GetResolution(),
		"Load Game",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	loadGameBtn->SetEnabled(false);
	m_elements.push_back(loadGameBtn);

	btnPosY += 0.15f;
	++focusID;

	auto settingsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		uiManager.GetResolution(),
		"Settings",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
		);
	settingsBtn->SetEnabled(false);
	m_elements.push_back(settingsBtn);

	btnPosY += 0.15f;
	++focusID;

	auto creditsBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		uiManager.GetResolution(),
		"Credits",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
		);
	creditsBtn->SetEnabled(false);
	m_elements.push_back(creditsBtn);

	btnPosY += 0.15f;
	++focusID;

	auto quitBtn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(btnPosX, btnPosY),
		GetElementSize(btnSizX, btnSizY),
		Alignment::MID_RIGHT,
		uiManager.GetResolution(),
		"Quit",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	quitBtn->SetOnClick([]() {AppContext::GetInstance().eventManager.InvokeEvent(CloseWindowEvent());});
	m_elements.push_back(quitBtn);

	auto title = std::make_shared<Title>(
		GetElementPosition(0.625f, 0.025f),
		GetElementSize(0.7f, 0.2f),
		Alignment::TOP_MID,
		false,
		uiManager.GetResolution(),
		appContext
		);
	m_elements.push_back(title);

	auto testText = std::make_shared<Text>(
		GetElementPosition(0.65f, 0.3f),
		GetElementSize(0.5f, 0.3f),
		Alignment::TOP_MID,
		0.02f,
		"jhjaskfdjhalkjsdflkjdshfalkjhfflakjsdhflkajsdhfkasjdfhlkajhsfaflkajsdhfalsdkfhafalksdjfhalksjdfhaslkdjfhaasdlkfjhasdkljfhasdlkfjhasdflkjh afha dflkjha flkajjh flkajhdf alkjhfd lakjhf klajdhf lakjdshf klajhsdf lakjdshf.",
		uiManager.GetResolution()
		);
	testText->LineBreaks(true);
	m_elements.push_back(testText);
}

MainMenu::MainMenu(Vector2 pos, Vector2 size, Alignment alignment, UIManager const& uiManager)
	: Scene(pos, size, alignment) {

	AppContext& appContext = AppContext::GetInstance();
	Initialize(uiManager, appContext);
}

void MainMenu::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
