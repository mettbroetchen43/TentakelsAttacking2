//
// PurpurTentakel
// 10.08.22
//

#include "GameManager.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "HPrint.h"
#include "CopyGalaxyType.hpp"
#include "HLogicAlias.hpp"
#include <cassert>
#include <algorithm>
#include <stdexcept>

// help Lambdas
static auto popup = [](std::string const& text) {
	ShowMessagePopUpEvent const popupEvent{
		"Invalid Input",
		text,
		[]() {}
	};
	AppContext::GetInstance().eventManager.InvokeEvent(popupEvent);
};
static auto message = [](std::string& messageText, std::string const& first, std::string const& second) {
	if (messageText.size() <= 0) { messageText = first; return; }

	messageText += ", " + second;
};

// player
bool GameManager::ValidAddPlayer() const {
	return {
		AppContext::GetInstance().constants.player.maxPlayerCount
		> m_players.size()
	};
}
unsigned int GameManager::GetNextPlayerID() const {
	unsigned int nextID{ 1 };
	while (true) {
		bool freeID{ true };
		for (auto p : m_players) {
			if (p->GetID() == nextID) {
				freeID = false;
				break;
			}
		}

		if (freeID) {
			return nextID;
		}

		++nextID;
	}
}

bool GameManager::IsExistingPlayerID(unsigned int ID) const {
	for (auto const& p : m_players) {
		if (p->GetID() == ID) {
			return true;
		}
	}
	return false;
}

bool GameManager::GetCurrentPlayer(Player_ty& currentPlayer) const {
	if (m_currentRoundPlayers.empty()) { return false; }

	currentPlayer = m_currentRoundPlayers.back();
	return true;
}
bool GameManager::GetNextPlayer(Player_ty& nextPlayer) const {
	if (m_currentRoundPlayers.size() < 2) { return false; }

	nextPlayer = m_currentRoundPlayers.at(m_currentRoundPlayers.size() - 2);
	return true;
}

void GameManager::AddPlayer(AddPlayerEvent const* event) {
	if (!ValidAddPlayer()) {
		ShowMessagePopUpEvent const UIEvent{
			"Max Player",
			"No more Player slots are available",
			[]() {}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(UIEvent);
		return;
	}

	unsigned int const newID{ GetNextPlayerID() };
	auto const player = std::make_shared<Player>(
		newID,
		PlayerType::HUMAN
	);
	m_players.push_back(player);

	AddPlayerUIEvent const AddEvent{
		newID,
		event->GetName(),
		event->GetColor()
	};
	AppContext::GetInstance().eventManager.InvokeEvent(AddEvent);
}
void GameManager::EditPlayer(EditPlayerEvent const* event) const {

	if (!IsExistingPlayerID(event->GetID())) {
		ShowMessagePopUpEvent const UIEvent{
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing",
			[]() {}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(UIEvent);
		return;
	}

	EditPlayerUIEvent const editEvent{
		event->GetID(),
		event->GetName(),
		event->GetColor()
	};
	AppContext::GetInstance().eventManager.InvokeEvent(editEvent);
}
void GameManager::DeletePlayer(DeletePlayerEvent const* event) {

	Player_ty toDelete{ nullptr };
	for (auto& p : m_players) {
		if (p->GetID() == event->GetID()) {
			toDelete = p;
			break;
		}
	}

	if (!toDelete) {
		ShowMessagePopUpEvent const messageEvent{
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing",
			[]() {}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(messageEvent);
		return;
	}

	m_players.erase(std::remove(
		m_players.begin(), m_players.end(), toDelete),
		m_players.end());

	DeletePlayerUIEvent const deleteEvent{ event->GetID() };
	AppContext::GetInstance().eventManager.InvokeEvent(deleteEvent);
}
void GameManager::ResetPlayer() {
	m_players.clear();

	ResetPlayerUIEvent const event{ };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void GameManager::CheckPlayerCount() const {

	AppContext_ty_c appContext{ AppContext::GetInstance() };
	bool valid;

	if (m_players.size() < appContext.constants.player.minPlayerCount) {
		ShowMessagePopUpEvent const event{
			"Player Count",
			"Not enough players.\n current min. Player Count: " + std::to_string(appContext.constants.player.minPlayerCount),
			[]() {}
		};
		appContext.eventManager.InvokeEvent(event);
		valid = false;
	}
	else if (m_players.size() > appContext.constants.player.maxPlayerCount) {
		ShowMessagePopUpEvent const event{
			"Player Count",
			"Too many players.\n current max Player Count: " + std::to_string(appContext.constants.player.maxPlayerCount),
			[]() {}
		};
		appContext.eventManager.InvokeEvent(event);
		valid = false;
	}
	else {
		valid = true;
	}

	ValidatePlayerCountResultEvent const event{ valid };
	appContext.eventManager.InvokeEvent(event);
}
void GameManager::ShuffleCurrentRoundPlayer() {
	std::shuffle(m_currentRoundPlayers.begin(), m_currentRoundPlayers.end(), m_random);
}

void GameManager::SendCurrentPlayerID() {
	unsigned int ID;
	Player_ty player{ nullptr };

	if (GetCurrentPlayer(player)) {
		ID = player->GetID();
	}
	else {
		ID = 0;
	}

	UpdateCurrentPlayerIDEvent const event{ ID };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void GameManager::SendNextPlayerID() {
	unsigned int ID;
	Player_ty player{ nullptr };

	if (GetNextPlayer(player)) {
		ID = player->GetID();
	}
	else {
		ID = 0;
	}

	UpdateNextPlayerIDEvent const event{ ID };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

// rounds
void GameManager::NextRound(bool valid) {

	if (!valid) { return; }

	AppContext_ty appContext{ AppContext::GetInstance() };
	// events and so on first
	Update();


	m_currentRoundPlayers = m_players;
	ShuffleCurrentRoundPlayer();

	m_galaxyManager.CopyGalaxies(CopyGalaxyType::COPY_ALL);

	SendCurrentPlayerID();
	SendNextPlayerID();

	++appContext.constants.global.currentRound;

	appContext.eventManager.InvokeEvent(ShowNextRoundEvent());
}
void GameManager::NextTurn(bool valid) {

	if (!valid) { return; }

	m_currentRoundPlayers.pop_back();

	m_galaxyManager.CopyGalaxies(CopyGalaxyType::COPY_START);

	SendCurrentPlayerID();
	SendNextPlayerID();

	AppContext::GetInstance().eventManager.InvokeEvent(ShowNextTurnEvent());
}
void GameManager::ValidateNextTurn() {

	if (m_currentRoundPlayers.size() <= 1) {
		ShowValidatePopUp const event{
			"next round?",
			"your turn will be over.",
			[this](bool valid) {
				this->NextRound(valid);
			}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		ShowValidatePopUp const event{
			"next player?",
			"your turn will be over.",
			[this](bool valid) {
				this->NextTurn(valid);
			}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

// events
void GameManager::SetGameEventActive(UpdateCheckGameEvent const* event) {
	if (event->GetType() == HGameEventType::GLOBAL) {
		for (auto e : settableGameEventTypes) {
			m_gameEvents[e] = event->GetIsChecked();
		}
	}
	else {
		m_gameEvents[event->GetType()] = event->GetIsChecked();
	}

	UpdateCheckGameEventsUI const updateEvent{ &m_gameEvents };
	AppContext::GetInstance().eventManager.InvokeEvent(updateEvent);
}

// Fleet
void GameManager::AddFleet(SendFleetInstructionEvent const* event) {

	if (!ValidateAddFleetInput(event)) { return; }

	Player_ty currentPlayer{ nullptr };
	if (!GetCurrentPlayer(currentPlayer)) { popup("No current player selected."); return; }

	bool const isValidFleet{ m_galaxyManager.AddFleet(event, currentPlayer) };
	ReturnFleetInstructionEvent const returnEvent{ isValidFleet };
	AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
}

bool GameManager::ValidateAddFleetInput(SendFleetInstructionEvent const* event) {

	std::string messageText;

	if (event->GetOrigin() <= 0) {
		message(messageText, "input in origin", "origin");
	}
	if (event->GetDestination() <= 0) {
		if ((event->GetDestinationX() <= 0) || (event->GetDestinationY() <= 0)) {
			message(messageText, "input in destination", "destination");
		}
	}
	if (event->GetShipCount() <= 0) {
		message(messageText, "input in ship count", "ship count");
	}
	if (!messageText.empty()) {
		messageText += " to low.";
		popup(messageText);
		return false;
	}

	bool const doubleDestination{
		event->GetDestination() > 0
		&& (event->GetDestinationX() > 0
			|| event->GetDestinationY() > 0) };
	if (doubleDestination) {
		popup("to many inputs for destination");
		return false;
	}

	return true;
}

// game
void GameManager::StartGame() {
	m_currentRoundPlayers = m_players;

	ShuffleCurrentRoundPlayer();
	SendCurrentPlayerID();
	SendNextPlayerID();
}

GameManager::GameManager()
	: m_galaxyManager{ this } {

	AppContext::GetInstance().eventManager.AddListener(this);
	for (auto e : settableGameEventTypes) {
		m_gameEvents[e] = true;
	}
	m_npcs[PlayerType::NEUTRAL] = std::make_shared<Player>(100, PlayerType::NEUTRAL);

	Print("GameManager", PrintType::INITIALIZE);
}

void GameManager::Update() {
	m_lastUpdateResults = m_galaxyManager.Update();
}

void GameManager::OnEvent(Event const& event) {

	// Player
	if (auto const* playerEvent = dynamic_cast<AddPlayerEvent const*>(&event)) {
		AddPlayer(playerEvent);
		return;
	}
	if (auto const* playerEvent = dynamic_cast<EditPlayerEvent const*>(&event)) {
		EditPlayer(playerEvent);
		return;
	}
	if (auto const* playerEvent = dynamic_cast<DeletePlayerEvent const*>(&event)) {
		DeletePlayer(playerEvent);
		return;
	}
	if (auto const* playerEvent = dynamic_cast<ResetPlayerEvent const*>(&event)) {
		ResetPlayer();
		return;
	}
	if (auto const* playerEvent = dynamic_cast<ValidatePlayerCountEvent const*>(&event)) {
		CheckPlayerCount();
		return;
	}
	if (auto const* playerEvent = dynamic_cast<LoadCurrentPlayerEvent const*>(&event)) {
		SendCurrentPlayerID();
		SendNextPlayerID();
		return;
	}

	// Events
	if (auto const* GameEvent = dynamic_cast<UpdateCheckGameEvent const*>(&event)) {
		SetGameEventActive(GameEvent);
		return;
	}
	if (auto const* GameEvent = dynamic_cast<InitialCheckGameEventDataEvent const*>(&event)) {
		UpdateCheckGameEventsUI const updateEvent{ &m_gameEvents };
		AppContext::GetInstance().eventManager.InvokeEvent(updateEvent);
		return;
	}

	// Galaxy
	if (auto const* galaxyEvent = dynamic_cast<GenerateGalaxyEvent const*>(&event)) {
		m_galaxyManager.GenerateGalaxy();
		return;
	}
	if (auto const* galaxyEvent = dynamic_cast<GetGalaxyPointerEvent const*>(&event)) {
		SendGalaxyPointerEvent const returnEvent{ m_galaxyManager.GetGalaxy(), false };
		AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
		return;
	}
	if (auto const* galaxyEvent = dynamic_cast<GetShowGalaxyPointerEvent const*> (&event)) {
		m_galaxyManager.GenerateShowGalaxy();
		return;
	}

	// Game
	if (auto const* gameEvent = dynamic_cast<StartGameEvent const*> (&event)) {
		StartGame();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<TriggerNextTurnEvent const*> (&event)) {
		ValidateNextTurn();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<GetUpdateEvaluation const*> (&event)) {
		AppContext::GetInstance().eventManager.InvokeEvent(SendUpdateEvaluation{ m_lastUpdateResults.first ,m_lastUpdateResults.second});
		return;
	}

	// Fleet
	if (auto const* fleetEvent = dynamic_cast<SendFleetInstructionEvent const*> (&event)) {
		AddFleet(fleetEvent);
		return;
	}
}
