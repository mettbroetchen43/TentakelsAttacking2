//
// Purpur Tentakel
// 06.10.2022
//

#include "NewGameScene.h"
#include "Title.h"
#include "Text.h"
#include "InputLine.hpp"
#include "ColorPicker.h"
#include "ClassicButton.h"
#include "Line.h"
#include "Table.h"
#include "UIManager.h"

void NewGameScene::Initialize(UIManager const& uiManager,
	AppContext& appContext) {
	auto title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		false,
		uiManager.GetResolution(),
		appContext
		);
	m_elements.push_back(title);

	auto addPlayerText = std::make_shared<Text>(
		GetElementPosition(0.1f, 0.28f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		0.05f,
		"Add Player:",
		uiManager.GetResolution()
		);
	m_elements.push_back(addPlayerText);

	auto inputLine = std::make_shared<InputLine<std::string>>(
		1,
		GetElementPosition(0.1f, 0.35f),
		GetElementSize(0.35f, 0.05f),
		Alignment::TOP_LEFT,
		20,
		uiManager.GetResolution()
		);
	inputLine->SetPlaceholderText("Player Name");
	m_elements.push_back(inputLine);

	auto colorPicker = std::make_shared<ColorPicker>(
		2,
		GetElementPosition(0.1f, 0.45f),
		GetElementSize(0.35f, 0.35f),
		Alignment::TOP_LEFT,
		uiManager.GetResolution()
		);
	m_elements.push_back(colorPicker);

	auto addPlayerBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.1f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_LEFT,
		uiManager.GetResolution(),
		"Add Player",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	m_elements.push_back(addPlayerBtn);

	auto removePlayerBtn = std::make_shared<ClassicButton>(
		4,
		GetElementPosition(0.45f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_RIGHT,
		uiManager.GetResolution(),
		"Remove Player",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(removePlayerBtn);

	auto line = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.25f),
		GetElementSize(0.0f, 0.7f),
		Alignment::TOP_MID,
		2.0f,
		uiManager.GetResolution()
		);
	m_elements.push_back(line);

	auto currentPlayerText = std::make_shared<Text>(
		GetElementPosition(0.55f, 0.28f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		0.05f,
		"Current Player:",
		uiManager.GetResolution()
		);
	m_elements.push_back(currentPlayerText);

	auto table = std::make_shared<Table>(
		GetElementPosition(0.9f, 0.35f),
		GetElementSize(0.35f, 0.45f),
		Alignment::TOP_RIGHT,
		5,
		appContext.MaxPlayerCount() + 1,
		3,
		uiManager.GetResolution()
		);
	table->SetRowEditable(0,false);
	table->SetColumnEditable(0,false);
	table->SetValue<StringCell, std::string>(0, 0, "ID");
	table->SetValue<StringCell, std::string>(0, 1, "Name");
	table->SetValue<StringCell, std::string>(0, 2, "Color");
	for (int i = 0; i < appContext.MaxPlayerCount();++i) {
		table->SetValue<IntCell, int>(i + 1, 0, i + 1);
	}
	m_elements.push_back(table);

	auto exitBtn = std::make_shared<ClassicButton>(
		6,
		GetElementPosition(0.55f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_LEFT,
		uiManager.GetResolution(),
		"Exit",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
		);
	exitBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::MAIN_MENU)
		);
	});
	m_elements.push_back(exitBtn);

	auto startGameBtn = std::make_shared<ClassicButton>(
		7,
		GetElementPosition(0.9f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_RIGHT,
		uiManager.GetResolution(),
		"Start",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	m_elements.push_back(startGameBtn);
}

NewGameScene::NewGameScene(Vector2 pos, Vector2 size, Alignment alignment,
	UIManager const& uiManager)
	: Scene(pos, size, alignment) {

	Initialize(uiManager, AppContext::GetInstance());
}

void NewGameScene::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}

void NewGameScene::Render(AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Render(appContext);
	}
}
void NewGameScene::Resize(Vector2 resolution, AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}
