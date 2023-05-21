//
// Purpur Tentakel
// 06.10.2022
//

#include "NewGamePlayer.h"
#include "Title.h"
#include "Text.h"
#include "ColorPicker.h"
#include "ClassicButton.h"
#include "GenerelEvents.hpp"
#include "Line.h"
#include "Table.h"
#include "UIManager.h"
#include "HFocusEvents.h"
#include <cassert>

void NewGamePlayerScene::Initialize(Vector2 resolution,
	AppContext& appContext) {

	auto title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		resolution,
		false,
		appContext
		);
	m_elements.push_back(title);

	auto addPlayerText = std::make_shared<Text>(
		GetElementPosition(0.1f, 0.28f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		resolution,
		Alignment::TOP_LEFT,
		0.05f,
		"Add Player:"
		);
	m_elements.push_back(addPlayerText);

	auto inputLine = std::make_shared<InputLine<std::string>>(
		1,
		GetElementPosition(0.1f, 0.35f),
		GetElementSize(0.35f, 0.05f),
		Alignment::TOP_LEFT,
		resolution,
		20
		);
	inputLine->SetPlaceholderText("Player Name");
	inputLine->SetOnEnter([this]() {
		this->AddPlayer();
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
	colorPicker->SetOnEnter([this]() {
		this->AddPlayer();
		});
	m_elements.push_back(colorPicker);
	m_nestedFocus.push_back(colorPicker.get());
	m_colorPicker = colorPicker.get();

	auto resetBTN = std::make_shared<ClassicButton>(
		7,
		GetElementPosition(0.45f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_RIGHT,
		resolution,
		"Reset",
		SoundType::ACCEPTED
		);
	resetBTN->SetOnClick([this]() {
		this->Reset();
		});
	m_elements.push_back(resetBTN);

	auto backBtn = std::make_shared<ClassicButton>(
		8,
		GetElementPosition(0.1f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_LEFT,
		resolution,
		"Back",
		SoundType::CLICKED_RELEASE_STD
		);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::MAIN_MENU)
		);
		});
	m_elements.push_back(backBtn);

	auto line = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.25f),
		GetElementSize(0.0f, 0.7f),
		Alignment::TOP_MID,
		resolution,
		2.0f
		);
	m_elements.push_back(line);

	auto currentPlayerText = std::make_shared<Text>(
		GetElementPosition(0.55f, 0.28f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		resolution,
		Alignment::TOP_LEFT,
		0.05f,
		"Current Player:"
		);
	m_elements.push_back(currentPlayerText);

	auto currentPlayerCount = std::make_shared<Text>(
		GetElementPosition(0.55f, 0.33f),
		GetElementSize(0.25f, 0.05f),
		Alignment::TOP_LEFT,
		resolution,
		Alignment::TOP_LEFT,
		0.02f,
		"current min player count: " + std::to_string(appContext.constants.player.minPlayerCount)
		);
	m_elements.push_back(currentPlayerCount);

	auto table = std::make_shared<Table>(
		GetElementPosition(0.9f, 0.35f),
		GetElementSize(0.35f, 0.45f),
		Alignment::TOP_RIGHT,
		resolution,
		5,
		static_cast<int>(appContext.constants.player.maxPlayerCount + 1),
		3,
		Vector2(0.33f,0.1f),
		0.1f
		);
	table->SetRowEditable(0, false);
	table->SetColumnEditable(0, false);
	table->SetHeadlineValues<std::string>({ "ID", "Name", "Color" });

	table->SetUpdateSpecificCell<std::string>(
		[this](AbstractTableCell const* cell, std::string oldValue, std::string newValue) {
			this->UpdatePlayerName(cell, oldValue, newValue);
		}
	);
	table->SetUpdateSpecificCell<Color>(
		[this](AbstractTableCell const* cell, Color oldValue, Color newValue) {
			UpdatePlayerColor(cell, oldValue, newValue);
		}
	);

	m_elements.push_back(table);
	m_nestedFocus.push_back(table.get());
	m_table = table.get();

	auto addPlayerBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.55f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_LEFT,
		resolution,
		"Add Player",
		SoundType::ACCEPTED
		);
	addPlayerBtn->SetOnClick([this]() {
		this->AddPlayer();
		});
	m_elements.push_back(addPlayerBtn);

	m_nextBTN = std::make_shared<ClassicButton>(
		6,
		GetElementPosition(0.9f, 0.85f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_RIGHT,
		resolution,
		"Next",
		SoundType::ACCEPTED
		);
	m_nextBTN->SetOnClick([this]() {
		this->CheckPlayerCount();
		});
	m_elements.push_back(m_nextBTN);

	InitializePlayerButtons(appContext);
}

void NewGamePlayerScene::InitializePlayerButtons(AppContext& appContext) {

	size_t const maxPlayerCount{ appContext.constants.player.maxPlayerCount };
	size_t const currentPlayerCount{ appContext.playerCollection.GetPlayerCount() };
	float const rowHeight{ 0.45f / (maxPlayerCount + 1) };
	float const initialY{ 0.35f + rowHeight };

	for (int i = 0; i < maxPlayerCount; ++i) {
		auto button = std::make_shared<ClassicButton>(
			100 + i,
			GetElementPosition(0.905f, initialY + rowHeight * i + 0.005f),
			GetElementSize(rowHeight * 0.7f, rowHeight - 0.01f),
			Alignment::TOP_LEFT,
			m_resolution,
			"X",
			SoundType::CLICKED_RELEASE_STD
			);

		button->SetEnabled(i < currentPlayerCount);
		button->SetOnClick([this, i]() {
			this->DeletePlayer(i + 1);
			});

		m_elements.push_back(button);
		m_playerButtons.push_back(button);
	}
}

void NewGamePlayerScene::CheckForNestedFocus(Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) const {
	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return;
	}

	for (auto f : m_nestedFocus) {
		if (!f->IsFocused()) { continue; }
		if (!f->IsNestedFocus()) { continue; }

		if (!CheckCollisionPointRec(mousePosition, f->GetCollider())) {
			f->SetNestedFocus(false);
			DeleteFocusLayer();
		}
	}
}

void NewGamePlayerScene::UpdateSceneEntries(AppContext const& appContext) {
	m_colorPicker->SetColor(appContext.playerCollection.GetPossibleColor());

	m_inputLine->Clear();
	if (m_colorPicker->IsNestedFocus()) {
		m_colorPicker->SetNestedFocus(false);
		DeleteFocusLayerEvent const focusEvent;
		appContext.eventManager.InvokeEvent(focusEvent);
	}

	SelectFocusElementEvent const event{m_inputLine};
	appContext.eventManager.InvokeEvent(event);
	
	auto const PlayerData{ appContext.playerCollection.GetPlayerData() };

	int index{ 1 };
	for (auto& p : PlayerData) {
		m_table->SetValue<int>        (index, 0, p.ID);
		m_table->SetValue<std::string>(index, 1, p.name);
		m_table->SetValue<Color>      (index, 2, p.color);

		m_table->SetSingleEditable(index, 1, true);
		m_table->SetSingleEditable(index, 2, true);

		unsigned int _ID{ p.ID };
		m_playerButtons.at(index - 1)->SetEnabled(true);
		m_playerButtons.at(index - 1)->SetOnClick([this, _ID]() {
			this->DeletePlayer(_ID);
			});

		++index;
	}
	for (int row = index; row < m_table->GetRowCount(); ++row) {
		for (int column = 0; column < m_table->GetColumnCount(); ++column) {
			m_table->SetValue<std::string>(row, column,"");
			m_table->SetSingleEditable    (row, column, false);
		}
		m_playerButtons.at(row - 1)->SetEnabled(false);
	}
}

void NewGamePlayerScene::AddPlayer() {
	AppContext const& appContext = AppContext::GetInstance();

	AddPlayerEvent const event{
		m_inputLine->GetValue(),
		m_colorPicker->GetColor()
	};
	appContext.eventManager.InvokeEvent(event);

	UpdateSceneEntries(appContext);
}
void NewGamePlayerScene::UpdatePlayer(unsigned int ID, std::string const& name,
	Color color, AppContext const& appContext) {

	EditPlayerEvent const event{
		ID,
		name,
		color
	};
	appContext.eventManager.InvokeEvent(event);

	UpdateSceneEntries(appContext);
}
void NewGamePlayerScene::UpdatePlayerName(AbstractTableCell const*,
	std::string oldValue, std::string newValue) {

	AppContext const& appContext{ AppContext::GetInstance() };
	PlayerData const playerData{ appContext.playerCollection.GetPlayerByName(oldValue) };

	UpdatePlayer(
		playerData.ID,
		newValue,
		playerData.color,
		appContext
	);
}
void NewGamePlayerScene::UpdatePlayerColor(AbstractTableCell const*,
	Color oldValue, Color newValue){
	AppContext const& appContext{ AppContext::GetInstance() };
	PlayerData const playerData{ appContext.playerCollection.GetPlayerByColor(oldValue) };

	UpdatePlayer(
		playerData.ID,
		playerData.name,
		newValue,
		appContext
	);
}
void NewGamePlayerScene::DeletePlayer(unsigned int ID) {
	AppContext const& appContext{ AppContext::GetInstance() };

	DeletePlayerEvent const event{ ID };
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	UpdateSceneEntries(appContext);
}
void NewGamePlayerScene::CheckPlayerCount() const {
	ValidatePlayerCountEvent const event;
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

void NewGamePlayerScene::NextScene(bool valid) {
	if (!valid) { return; }

	SwitchSceneEvent const event{ SceneType::NEW_GAME_PARAMETER };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void NewGamePlayerScene::Reset() {
	AppContext const& appContext{ AppContext::GetInstance() };

	ResetPlayerEvent const event;
	appContext.eventManager.InvokeEvent(event);

	UpdateSceneEntries(appContext);
}

void NewGamePlayerScene::SetNextButton(AppContext const& appContext) {
	size_t const playerCount{ appContext.playerCollection.GetPlayerData().size() };
	bool const validPlayerCount{
			playerCount >= appContext.constants.player.minPlayerCount
		and playerCount <= appContext.constants.player.maxPlayerCount 
	};

	if (validPlayerCount != m_nextBTN->IsEnabled()) {
		m_nextBTN->SetEnabled(validPlayerCount);
	}
}

NewGamePlayerScene::NewGamePlayerScene(Vector2 resolution)
	: Scene{ {0.0f,0.0f}, {1.0f,1.0f}, Alignment::DEFAULT, resolution } {

	AppContext& appContext{ AppContext::GetInstance() };
	Initialize(resolution, appContext);
	UpdateSceneEntries(appContext);
	appContext.eventManager.AddListener(this);
}
NewGamePlayerScene::~NewGamePlayerScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void NewGamePlayerScene::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	CheckForNestedFocus(mousePosition, appContext);

	SetNextButton(appContext);

	for (auto& e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}
void NewGamePlayerScene::Render(AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Render(appContext);
	}
}
void NewGamePlayerScene::Resize(Vector2 resolution,
	AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}

void NewGamePlayerScene::OnEvent(Event const& event) {

	if (auto const* CountEvent = dynamic_cast<ValidatePlayerCountResultEvent const*>(&event)) {
		NextScene(CountEvent->GetValid());
		return;
	}
}
