//
// Purpur Tentakel
// 21.11.2022
//

#include "MainScene.h"
#include "GalaxyAndSlider.h"
#include "PlanetTable.h"
#include "FleetTable.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "GenerelEvents.hpp"
#include "HPlayerCollection.h"
#include "Title.h"
#include "Text.h"
#include "InputLine.hpp"
#include "HPrint.h"
#include <cassert>


void MainScene::Initialize() {

	AppContext& appContext = AppContext::GetInstance();

	// Title
	auto title = std::make_shared<Title>(
		GetElementPosition(0.31f, 0.0f),
		GetElementSize(0.55f, 0.2f),
		Alignment::TOP_MID,
		m_resolution,
		false,
		AppContext::GetInstance()
		);
	m_elements.push_back(title);

	// Btn
	auto settingsBtn = std::make_shared<ClassicButton>(
		5,
		GetElementPosition(0.95f, 0.02f),
		GetElementSize(0.05f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"settings",
		SoundType::CLICKED_RELEASE_STD
		);
	settingsBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::SETTINGS));
		});
	m_elements.push_back(settingsBtn);


	auto galaxyBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.7f, 0.02f),
		GetElementSize(0.1f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"galaxy",
		SoundType::CLICKED_RELEASE_STD
		);
	galaxyBtn->SetOnClick([this]() {
		this->Switch(MainSceneType::GALAXY);
		});
	m_elements.push_back(galaxyBtn);

	auto planetTableBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(0.8f, 0.02f),
		GetElementSize(0.1f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"planet table",
		SoundType::CLICKED_RELEASE_STD
		);
	planetTableBtn->SetOnClick([this]() {
		this->Switch(MainSceneType::PLANET_TABLE);
		});
	m_elements.push_back(planetTableBtn);

	auto fleetTableBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.9f, 0.02f),
		GetElementSize(0.1f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"fleet table",
		SoundType::CLICKED_RELEASE_STD
		);
	fleetTableBtn->SetOnClick([this]() {
		this->Switch(MainSceneType::FLEET_TABLE);
		});
	m_elements.push_back(fleetTableBtn);

	m_nextBtn = std::make_shared<ClassicButton>(
		4,
		GetElementPosition(0.99f, 0.95f),
		GetElementSize(0.1f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"next Player",
		SoundType::ACCEPTED
		);
	m_nextBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(TriggerNextTurnEvent());
		});
	m_elements.push_back(m_nextBtn);

	// text
	auto currentPlayerLabel = std::make_shared<Text>(
		GetElementPosition(0.7f, 0.08f),
		GetElementSize(0.1f, 0.02f),
		Alignment::TOP_RIGHT,
		m_resolution,
		Alignment::TOP_RIGHT,
		0.02f,
		"current player:"
		);
	// currentPlayerLabel->RenderRectangle(true);
	m_elements.push_back(currentPlayerLabel);

	m_currentPlayerName = std::make_shared<Text>(
		GetElementPosition(0.71f, 0.08f),
		GetElementSize(0.2f, 0.02f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		"" 
		);
	// m_currentPlayerName->RenderRectangle(true);
	m_elements.push_back(m_currentPlayerName);


	auto currentRoundLabel = std::make_shared<Text>(
		GetElementPosition(0.7f, 0.1f),
		GetElementSize(0.1f, 0.02f),
		Alignment::TOP_RIGHT,
		m_resolution,
		Alignment::TOP_RIGHT,
		0.02f,
		"current round:"
		);
	// currentRoundLabel->RenderRectangle(true);
	m_elements.push_back(currentRoundLabel);

	m_currentRound = std::make_shared<Text>(
		GetElementPosition(0.71f, 0.1f),
		GetElementSize(0.2f, 0.02f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		std::to_string(appContext.constants.global.currentRound)
		);
	// m_currentRound->RenderRectangle(true);
	m_elements.push_back(m_currentRound);


	auto currentTargetRoundLabel = std::make_shared<Text>(
		GetElementPosition(0.7f, 0.12f),
		GetElementSize(0.1f, 0.02f),
		Alignment::TOP_RIGHT,
		m_resolution,
		Alignment::TOP_RIGHT,
		0.02f,
		"target round:"
		);
	// currentTargetRoundLabel->RenderRectangle(true);
	m_elements.push_back(currentTargetRoundLabel);

	m_currentTargetRound = std::make_shared<Text>(
		GetElementPosition(0.71f, 0.12f),
		GetElementSize(0.2f, 0.02f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		std::to_string(appContext.constants.global.currentTargetRound)
		);
	// m_currentTargetRound->RenderRectangle(true);
	m_elements.push_back(m_currentTargetRound);


	auto nextPlayerNameLabel = std::make_shared<Text>(
		GetElementPosition(0.9f, 0.98f),
		GetElementSize(0.1f, 0.02f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.02f,
		"next player:"
		);
	// nextPlayerNameLabel->RenderRectangle(true);
	m_elements.push_back(nextPlayerNameLabel);

	m_nextPlayerName = std::make_shared<Text>(
		GetElementPosition(0.91f, 0.98f),
		GetElementSize(0.25f, 0.02f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		Alignment::BOTTOM_LEFT,
		0.02f,
		""
		);
	// m_nextPlayerName->RenderRectangle(true);
	m_elements.push_back(m_nextPlayerName);

	// ship input
	auto text = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.25f),
		GetElementSize(0.2f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.03f,
		"origin:"
	);
	m_elements.push_back(text);

	m_origin = std::make_shared<InputLine<int>>(
		1000,
		GetElementPosition(0.99f, 0.25f),
		GetElementSize(0.08f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		3
	);
	m_origin->SetOnEnter([this]() {
		this->SendFleetInstruction();
		});
	m_origin->SetOnValueChanced([this]() {
			SetAcceptButon();
		});
	m_origin->SetPlaceholderText("ID");
	m_elements.push_back(m_origin);

	text = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.32f),
		GetElementSize(0.2f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.03f,
		"destination:"
		);
	m_elements.push_back(text);

	m_destination = std::make_shared<InputLine<int>>(
		1001,
		GetElementPosition(0.99f, 0.32f),
		GetElementSize(0.08f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		3
		);
	m_destination->SetOnEnter([this]() {
		this->SendFleetInstruction();
		});
	m_destination->SetOnValueChanced([this]() {
		SetAcceptButon();
		});
	m_destination->SetPlaceholderText("ID");
	m_elements.push_back(m_destination);

	m_destinationX = std::make_shared<InputLine<int>>(
		1002,
		GetElementPosition(0.949f, 0.37f),
		GetElementSize(0.039f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		3
		);
	m_destinationX->SetOnEnter([this]() {
		this->SendFleetInstruction();
		});
	m_destinationX->SetOnValueChanced([this]() {
		SetAcceptButon();
		});
	m_destinationX->SetPlaceholderText("X");
	m_elements.push_back(m_destinationX);

	m_destinationY = std::make_shared<InputLine<int>>(
		1003,
		GetElementPosition(0.99f, 0.37f),
		GetElementSize(0.039f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		3
		);
	m_destinationY->SetOnEnter([this]() {
		this->SendFleetInstruction();
		});
	m_destinationY->SetOnValueChanced([this]() {
		SetAcceptButon();
		});
	m_destinationY->SetPlaceholderText("Y");
	m_elements.push_back(m_destinationY);

	text = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.47f),
		GetElementSize(0.2f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.03f,
		"ship count:"
		);
	m_elements.push_back(text);

	m_shipCount = std::make_shared<InputLine<int>>(
		1004,
		GetElementPosition(0.99f, 0.47f),
		GetElementSize(0.08f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		4
		);
	m_shipCount->SetOnEnter([this]() {
		this->SendFleetInstruction();
		});
	m_shipCount->SetOnValueChanced([this]() {
		SetAcceptButon();
		});
	m_shipCount->SetPlaceholderText("Count");
	m_elements.push_back(m_shipCount);

	m_acceptBtn = std::make_shared<ClassicButton>(
		1005,
		GetElementPosition(0.99f, 0.54f),
		GetElementSize(0.04f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"+",
		SoundType::ACCEPTED
		);
	m_acceptBtn->SetOnClick([this]() {
		this->SendFleetInstruction();
		});
	m_elements.push_back(m_acceptBtn);

	m_resetBtn = std::make_shared<ClassicButton>(
		1006,
		GetElementPosition(0.95f, 0.54f),
		GetElementSize(0.04f, 0.04f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"X",
		SoundType::ACCEPTED
		);
	m_resetBtn->SetOnClick([this]() {
		this->ClearInputLines();
		});
	m_elements.push_back(m_resetBtn);
}
void MainScene::InitializeGalaxy() {
	AppContext& appContext = AppContext::GetInstance();
	if (m_galaxy) {
		m_galaxy->SetActive(false, appContext);
		m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_galaxy), m_elements.end());
		m_galaxy = nullptr;
	}

	m_galaxy = std::make_shared<GalaxyScene>(
		GetElementPosition(0.01f, 0.99f),
		GetElementSize(0.85f, 0.85f),
		Alignment::BOTTOM_LEFT,
		m_resolution
		);
	m_elements.push_back(m_galaxy);
}
void MainScene::InitializePlanetTable() {

	AppContext& appContext = AppContext::GetInstance();
	if (m_planetTable) {
		m_planetTable->SetActive(false, appContext);
		m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_planetTable), m_elements.end());
		m_planetTable = nullptr;
	}

	m_planetTable = std::make_shared<PlanetTable>(
		GetElementPosition(0.01f, 0.95f),
		GetElementSize(0.85f, 0.78f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		m_galaxy->GetGalaxy()
		);
	m_elements.push_back(m_planetTable);
}
void MainScene::InitializeFleetTable() {
	 
	AppContext& appContext = AppContext::GetInstance();
	if (m_fleetTable) {
		m_fleetTable->SetActive(false, appContext);
		m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_fleetTable), m_elements.end());
		m_fleetTable = nullptr;
	}

	m_fleetTable = std::make_shared<FleetTable>(
		GetElementPosition(0.01f, 0.95f),
		GetElementSize(0.85f, 0.78f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		m_galaxy->GetGalaxy()
	);
	m_elements.push_back(m_fleetTable);
}

void MainScene::NextTurn() {
	AppContext const& appContext = AppContext::GetInstance();
	Switch(MainSceneType::CLEAR);
	SetPlayerText();
	InitializeGalaxy();

	auto event = ShowMessagePopUpEvent(
		"start turn?",
		"next plyer: " + m_currentPlayer.name + "\naccept to start your turn",
		[this]() {
			this->Switch(MainSceneType::GALAXY);
		}
	);
	appContext.eventManager.InvokeEvent(event);
}
void MainScene::NextRound() {
	AppContext& appContext = AppContext::GetInstance();

	SetPlayerText();
	InitializeGalaxy();
	InitializePlanetTable();
	InitializeFleetTable();

	m_currentRound->SetText(std::to_string(appContext.constants.global.currentRound));
	m_currentTargetRound->SetText(std::to_string(appContext.constants.global.currentTargetRound));

	auto event = ShowMessagePopUpEvent(
		"start round",
		"next round is starting\n just for debug to know"
	);
	appContext.eventManager.InvokeEvent(event);

	Switch(MainSceneType::GALAXY);
}

void MainScene::SetPlayerText() {

	m_currentPlayerName->SetText(m_currentPlayer.name);
	m_currentPlayerName->SetColor(m_currentPlayer.color);

	m_nextPlayerName->SetText(m_nextPlayer.name);
	m_nextPlayerName->SetColor(m_nextPlayer.color);
}

void MainScene::Switch(MainSceneType sceneType) {
	AppContext& appContext = AppContext::GetInstance();

	assert(m_galaxy);
	assert(m_planetTable);

	m_galaxy->SetActive(false, appContext);
	m_planetTable->SetActive(false, appContext);
	m_fleetTable->SetActive(false, appContext);

	m_galaxy->SetActive(sceneType == MainSceneType::GALAXY, appContext);
	m_planetTable->SetActive(sceneType == MainSceneType::PLANET_TABLE, appContext);
	m_fleetTable->SetActive(sceneType == MainSceneType::FLEET_TABLE, appContext);
}

bool MainScene::HasAnyInputLineFocus() {
	
	if (m_origin->IsFocused()) { return true; }
	if (m_destination->IsFocused()) { return true; }
	if (m_destinationX->IsFocused()) { return true; }
	if (m_destinationY->IsFocused()) { return true; }
	if (m_shipCount->IsFocused()) { return true; }

	return false;
} 

void MainScene::SetAcceptButon() {

	bool valid =
		m_origin->HasValue()
		&& (m_destination->HasValue()
			or (m_destinationX->HasValue()
			&& m_destinationY->HasValue()))
		&& m_shipCount->HasValue();

	m_acceptBtn->SetEnabled(valid);
}

void MainScene::SendFleetInstruction() {

	// TODO: validate input -> implement validation in logic first

	auto event = SendFleedInstructionEvent(
		m_origin->GetValue(),
		m_destination->GetValue(),
		m_destinationX->GetValue(),
		m_destinationY->GetValue(),
		m_shipCount->GetValue()
	);
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void MainScene::ClearInputLines() {

	m_origin->Clear();
	m_destination->Clear();
	m_destinationX->Clear();
	m_destinationY->Clear();
	m_shipCount->Clear();

	auto event = SelectFocusElementEvent(m_origin.get());
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

MainScene::MainScene(Vector2 resolution)
	: Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution) {

	AppContext& appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);
	appContext.eventManager.InvokeEvent(LoadCurrentPlayerEvent());

	Initialize();
	InitializeGalaxy();
	InitializePlanetTable();
	InitializeFleetTable();
	SetPlayerText();
	Switch(MainSceneType::GALAXY);
	SetAcceptButon();
}
MainScene::~MainScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void MainScene::OnEvent(Event const& event) {
	AppContext const& appContext = AppContext::GetInstance();
	
	// player
	if (auto const* playerEvent = dynamic_cast<UpdateCurrentPlayerIDEvent const*>(&event)) {
		m_currentPlayer = appContext.playerCollection.GetPlayerByID(playerEvent->GetID());
		return;
	}
	if (auto const* playerEvent = dynamic_cast<UpdateNextPlayerIDEvent const*>(&event)) {
		m_nextPlayer = appContext.playerCollection.GetPlayerByID(playerEvent->GetID());
		return;
	}

	// turns and rounds
	if (auto const* playerEvent = dynamic_cast<ShowNextTurnEvent const*>(&event)) {
		NextTurn();
		return;
	}
	if (auto const* playerEvent = dynamic_cast<ShowNextRoundEvent const*>(&event)) {
		NextRound();
		return;
	}

	// Fleet Instruction
	if (auto const* fleetEvent = dynamic_cast<ReturnFleetInstructionEvent const*>(&event)) {
		if (fleetEvent->IsValidFleet()) {
			ClearInputLines();
			InitializePlanetTable();
			InitializeFleetTable();
		}
		return;
	}
}

void MainScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

	if (!HasAnyInputLineFocus()) {

		bool setFocus = false;
		auto input = GetKeyPressed();
		if (input != 0) {

			if (48 <= input && input <= 57) {
				setFocus = true;
			}
			if (320 <= input && input <= 329) {
				setFocus = true;
			}
		}

		if (setFocus) {
			auto event = SelectFocusElementEvent(m_origin.get());
			appContext.eventManager.InvokeEvent(event);
		}
	}


	Scene::CheckAndUpdate(mousePosition, appContext);
}
