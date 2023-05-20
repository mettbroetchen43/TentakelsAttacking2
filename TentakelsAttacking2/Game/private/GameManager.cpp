//
// PurpurTentakel
// 10.08.22
//

#include "GameManager.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "HPrint.h"
#include <cassert>
#include <algorithm>
#include <stdexcept>

enum class CopyGalaxyType {
	COPY_ALL,
	COPY_START,
};

// help Lambdas
static auto popup = [](std::string const& text) {
	ShowMessagePopUpEvent const popupEvent{ "Invalid Input", text };
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

bool GameManager::GetCurrentPlayer(std::shared_ptr<Player>& currentPlayer) const {
	if (m_currentRoundPlayers.empty()) { return false; }

	currentPlayer = m_currentRoundPlayers.back();
	return true;
}
bool GameManager::GetNextPlayer(std::shared_ptr<Player>& nextPlayer) const {
	if (m_currentRoundPlayers.size() < 2) { return false; }

	nextPlayer = m_currentRoundPlayers.at(m_currentRoundPlayers.size() - 2);
	return true;
}

void GameManager::AddPlayer(AddPlayerEvent const* event) {
	if (!ValidAddPlayer()) {
		ShowMessagePopUpEvent const UIEvent{
			"Max Player",
			"No more Player slots are available"
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
			"ID " + std::to_string(event->GetID()) + " is not existing"
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

	std::shared_ptr<Player> toDelete{ nullptr };
	for (auto& p : m_players) {
		if (p->GetID() == event->GetID()) {
			toDelete = p;
			break;
		}
	}

	if (!toDelete) {
		ShowMessagePopUpEvent const messageEvent{
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing"
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

	AppContext const& appContext{ AppContext::GetInstance() };
	bool valid;

	if (m_players.size() < appContext.constants.player.minPlayerCount) {
		ShowMessagePopUpEvent const event{
			"Player Count",
			"Not enough players.\n current min. Player Count: " + std::to_string(appContext.constants.player.minPlayerCount) 
		};
		appContext.eventManager.InvokeEvent(event);
		valid = false;
	}
	else if (m_players.size() > appContext.constants.player.maxPlayerCount) {
		ShowMessagePopUpEvent const event{
			"Player Count",
			"Too many players.\n current max Player Count: " + std::to_string(appContext.constants.player.maxPlayerCount)
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
	std::shared_ptr<Player> player{ nullptr };

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
	std::shared_ptr<Player> player{ nullptr };

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

	AppContext& appContext{ AppContext::GetInstance() };
	// events and so on first


	m_currentRoundPlayers = m_players;
	ShuffleCurrentRoundPlayer();

	CopyGalaxies(CopyGalaxyType::COPY_ALL);

	SendCurrentPlayerID();
	SendNextPlayerID();

	++appContext.constants.global.currentRound;

	appContext.eventManager.InvokeEvent(ShowNextRoundEvent());
}
void GameManager::NextTurn(bool valid) {

	if (!valid) { return; }

	m_currentRoundPlayers.pop_back();

	CopyGalaxies(CopyGalaxyType::COPY_START);

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

void GameManager::FilterCurrentGalaxy() {
	std::shared_ptr<Player> currentPlayer{ nullptr };
	bool const valid{ GetCurrentPlayer(currentPlayer) };
	if (not valid) { return; }
	m_currentGalaxy->FilterByPlayer(currentPlayer->GetID());
}

// events
void GameManager::SetGameEventActive(UpdateCheckGameEvent const* event) {
	if (event->GetType() == GameEventType::GLOBAL) {
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

// galaxy
void GameManager::GenerateGalaxy() {
	AppContext const& appContext{ AppContext::GetInstance() };
	Vec2<int> const size = {
		appContext.constants.world.currentDimensionX,
		appContext.constants.world.currentDimensionY
	};
	auto const galaxy = std::make_shared<Galaxy>(
		size,
		appContext.constants.world.currentPlanetCount,
		m_players,
		m_npcs[PlayerType::NEUTRAL]
	);

	if (galaxy->IsValid()) {
		m_mainGalaxy = galaxy;
		CopyGalaxies(CopyGalaxyType::COPY_ALL);
		GalaxyGeneratedUIEvent const event{ };
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		ShowMessagePopUpEvent const event{
			"Galaxy",
			"Unable to generate the Galaxy.\nTo many Plantes."
		};
		appContext.eventManager.InvokeEvent(event);
	}
}
void GameManager::GenerateShowGalaxy() {
	AppContext const& appContext{ AppContext::GetInstance() };
	Vec2<int> const size = {
		appContext.constants.world.showDimensionX,
		appContext.constants.world.showDimensionY,
	};

	auto const galaxy = std::make_shared<Galaxy>(
		size,
		appContext.constants.world.showPlanetCount,
		m_players,
		m_npcs[PlayerType::NEUTRAL]
	);

	if (galaxy->IsValid()) {
		m_showGalaxy = galaxy;
		SendGalaxyPointerEvent const event{ m_showGalaxy.get(), true };
		appContext.eventManager.InvokeEvent(event);
	}
	else if (m_showGalaxy) {
		SendGalaxyPointerEvent const event{ m_showGalaxy.get(), true };
		appContext.eventManager.InvokeEvent(event);
		Print("Could not generated ShowGalaxy -> Use old Galaxy", PrintType::EXPECTED_ERROR);
	}
	else {
		Print("Could not generated ShowGalaxy -> No Galaxy", PrintType::ERROR);
	}
}

void GameManager::CopyGalaxies(CopyGalaxyType copyType) {
	if (copyType == CopyGalaxyType::COPY_ALL) {
		m_startGalaxy = std::make_shared<Galaxy>(*m_mainGalaxy);
	}
	m_currentGalaxy = std::make_shared<Galaxy>(*m_startGalaxy);
	FilterCurrentGalaxy();
}

// Fleet
void GameManager::AddFleet(SendFleetInstructionEvent const* event) {

	if (!ValidateAddFleetInput(event)) { return; }

	std::shared_ptr<Player> currentPlayer{ nullptr };
	if (!GetCurrentPlayer(currentPlayer)) { popup("No current player selected."); return; }

	bool const isValidFleet{ m_mainGalaxy->AddFleet(event, currentPlayer) };
	bool const validCurrentFleet{ m_currentGalaxy->AddFleet(event, currentPlayer) };
	if (not validCurrentFleet) { Print("Not able to add Fleet to current Galaxy", PrintType::ERROR); }

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

GameManager::GameManager() {
	AppContext::GetInstance().eventManager.AddListener(this);
	for (auto e : settableGameEventTypes) {
		m_gameEvents[e] = true;
	}
	m_npcs[PlayerType::NEUTRAL] = std::make_shared<Player>(100, PlayerType::NEUTRAL);

	Print("GameManager", PrintType::INITIALIZE);
}

void GameManager::Update() {
	/*
	preUpdate -> moving and stuff
	Update -> general update
	postUpdate -> cleanup
	*/
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
		GenerateGalaxy();
		return;
	}
	if (auto const* galaxyEvent = dynamic_cast<GetGalaxyPointerEvent const*>(&event)) {
		SendGalaxyPointerEvent const returnEvent{ m_currentGalaxy.get(), false };
		AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
		return;
	}
	if (auto const* galaxyEvent = dynamic_cast<GetShowGalaxyPointerEvent const*> (&event)) {
		GenerateShowGalaxy();
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

	// Fleet
	if (auto const* fleetEvent = dynamic_cast<SendFleetInstructionEvent const*> (&event)) {
		AddFleet(fleetEvent);
		return;
	}
}
