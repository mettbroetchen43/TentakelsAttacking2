//
// Purpur Tentakel
// 06.10.2022
//

#include "NewGameScene.h"
#include "Title.h"
#include "Text.h"
#include "ColorPicker.h"
#include "ClassicButton.h"
#include "GenerelEvents.hpp"
#include "Line.h"
#include "Table.h"
#include "UIManager.h"
#include <cassert>

void NewGameScene::Initialize(Vector2 resolution, AppContext& appContext) {
	auto title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		false,
		resolution,
		appContext
		);
	m_elements.push_back(title);

	auto addPlayerText = std::make_shared<Text>(
		GetElementPosition(0.1f, 0.28f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		0.05f,
		"Add Player:",
		resolution
		);
	m_elements.push_back(addPlayerText);

	auto inputLine = std::make_shared<InputLine<std::string>>(
		1,
		GetElementPosition(0.1f, 0.35f),
		GetElementSize(0.35f, 0.05f),
		Alignment::TOP_LEFT,
		20,
		resolution
		);
	inputLine->SetPlaceholderText("Player Name");
	inputLine->SetOnEnter([&]() {
		AddPlayer();
		});
	m_elements.push_back(inputLine);
	m_inputLine = inputLine.get();

	auto colorPicker = std::make_shared<ColorPicker>(
		2,
		GetElementPosition(0.1f, 0.45f),
		GetElementSize(0.35f, 0.35f),
		Alignment::TOP_LEFT,
		resolution
		);
	colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());
	colorPicker->SetOnEnter([&]() {
		AddPlayer();
		});
	m_elements.push_back(colorPicker);
	m_nestedFocus.push_back(colorPicker.get());
	m_colorPicker = colorPicker.get();

	auto addPlayerBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.45f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_RIGHT,
		resolution,
		"Add Player",
		SoundType::ACCEPTED
		);
	addPlayerBtn->SetOnClick([&]() {
		AddPlayer();
		});
	m_elements.push_back(addPlayerBtn);

	auto removePlayerBtn = std::make_shared<ClassicButton>(
		4,
		GetElementPosition(0.1f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_LEFT,
		resolution,
		"Remove Player",
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(removePlayerBtn);

	auto line = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.25f),
		GetElementSize(0.0f, 0.7f),
		Alignment::TOP_MID,
		2.0f,
		resolution
		);
	m_elements.push_back(line);

	auto currentPlayerText = std::make_shared<Text>(
		GetElementPosition(0.55f, 0.28f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		0.05f,
		"Current Player:",
		resolution
		);
	m_elements.push_back(currentPlayerText);

	auto table = std::make_shared<Table>(
		GetElementPosition(0.9f, 0.35f),
		GetElementSize(0.35f, 0.45f),
		Alignment::TOP_RIGHT,
		5,
		appContext.playerCollection.MaxPlayerCount() + 1,
		3,
		resolution
		);
	table->SetRowEditable(0, false);
	table->SetColumnEditable(0, false);
	table->SetHeadlines({ "ID", "Name", "Color" }, false);
	table->ResizeCells();
	m_elements.push_back(table);
	m_nestedFocus.push_back(table.get());
	m_table = table.get();

	auto startGameBtn = std::make_shared<ClassicButton>(
		6,
		GetElementPosition(0.9f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_RIGHT,
		resolution,
		"Start",
		SoundType::ACCEPTED
		);
	m_elements.push_back(startGameBtn);

	auto exitBtn = std::make_shared<ClassicButton>(
		7,
		GetElementPosition(0.55f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_LEFT,
		resolution,
		"Exit",
		SoundType::CLICKED_RELEASE_STD
		);
	exitBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::MAIN_MENU)
		);
		});
	m_elements.push_back(exitBtn);
}

void NewGameScene::CheckForNestedFocus(Vector2 const& mousePosition,
	AppContext const& appContext) const {
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return;
	}

	for (auto f : m_nestedFocus) {
		if (!f->IsFocused()) { continue; }
		if (!f->IsNestedFocus()) { continue; }

		if (!CheckCollisionPointRec(mousePosition, f->GetCollider())) {
			f->SetNestedFocus(false);
			auto event = DeleteFocusLayerEvent();
			appContext.eventManager.InvokeEvent(event);
		}
	}
}

void NewGameScene::UpdateSceneEntries(AppContext const& appContext) {
	m_colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());
	
	m_inputLine->Clear();
	if (m_colorPicker->IsNestedFocus()) {
		m_colorPicker->SetNestedFocus(false);
		auto focusEvent = DeleteFocusLayerEvent();
		appContext.eventManager.InvokeEvent(focusEvent);
	}

	auto event = SelectFocusElementEvent(m_inputLine);
	appContext.eventManager.InvokeEvent(event);

	auto playerNames = appContext.playerCollection.GetNames();
	auto playerColors = appContext.playerCollection.GetColors();

	assert(playerNames.size() == playerColors.size());
	
	int index = 1;
	for (auto& [ID, name] : playerNames) {
		m_table->SetValue<IntCell, int>(index, 0, ID, false);
		m_table->SetValue<StringCell, std::string>(index, 1, name, false);
		m_table->SetValue<ColorCell, Color>(index, 2, playerColors.at(ID), false);
	
		++index;
	}
	m_table->ResizeCells();
}

void NewGameScene::AddPlayer() {
	AppContext& appContext = AppContext::GetInstance();

	auto event = AddPlayerEvent(
		m_inputLine->GetValue(),
		m_colorPicker->GetColor()
	);
	appContext.eventManager.InvokeEvent(event);

	UpdateSceneEntries(appContext);
}

NewGameScene::NewGameScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment) {

	Initialize(resolution, AppContext::GetInstance());
}

void NewGameScene::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	CheckForNestedFocus(mousePosition, appContext);

	for (auto& e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}
void NewGameScene::Render(AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Render(appContext);
	}
}
void NewGameScene::Resize(Vector2 resolution,
	AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}
