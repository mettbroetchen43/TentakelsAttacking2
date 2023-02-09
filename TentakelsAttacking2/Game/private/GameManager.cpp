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

// help Labmdas
static auto popup = [](std::string const& text) {
	auto popupEvent = ShowMessagePopUpEvent("Invalid Input", text);
	AppContext::GetInstance().eventManager.InvokeEvent(popupEvent);
};
static auto message = [](std::string& messageText, std::string const& first, std::string const& second) {
	if (messageText.size() <= 0) { messageText = first; return; }

	messageText += ", " + second;
};

// player
bool GameManager::ValidAddPlayer() const {
	return AppContext::GetInstance().constants.player.maxPlayerCount
		> m_players.size();
}
unsigned int GameManager::GetNextPlayerID() const {
	unsigned int nextID = 1;
	while (true) {
		bool freeID = true;
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
		auto UIEvent = ShowMessagePopUpEvent(
			"Max Player",
			"No more Player slots are available"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(UIEvent);
		return;
	}

	unsigned int newID = GetNextPlayerID();
	auto player = std::make_shared<Player>(
		newID,
		PlayerType::HUMAN
		);
	m_players.push_back(player);

	auto AddEvent = AddPlayerUIEvent(
		newID,
		event->GetName(),
		event->GetColor()
	);
	AppContext::GetInstance().eventManager.InvokeEvent(AddEvent);
}
void GameManager::EditPlayer(EditPlayerEvent const* event) const {

	if (!IsExistingPlayerID(event->GetID())) {
		auto UIEvent = ShowMessagePopUpEvent(
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(UIEvent);
		return;
	}

	auto editEvent = EditPlayerUIEvent(
		event->GetID(),
		event->GetName(),
		event->GetColor()
	);
	AppContext::GetInstance().eventManager.InvokeEvent(editEvent);
}
void GameManager::DeletePlayer(DeletePlayerEvent const* event) {

	std::shared_ptr<Player> toDelete = nullptr;
	for (auto& p : m_players) {
		if (p->GetID() == event->GetID()) {
			toDelete = p;
			break;
		}
	}

	if (!toDelete) {
		auto messageEvent = ShowMessagePopUpEvent(
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(messageEvent);
		return;
	}

	m_players.erase(std::remove(
		m_players.begin(), m_players.end(), toDelete),
		m_players.end());

	auto deleteEvent = DeletePlayerUIEvent(event->GetID());
	AppContext::GetInstance().eventManager.InvokeEvent(deleteEvent);
}
void GameManager::ResetPlayer() {
	m_players.clear();

	auto event = ResetPlayerUIEvent();
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void GameManager::CheckPlayerCount() const {

	AppContext& appContext = AppContext::GetInstance();
	bool valid;

	if (m_players.size() < appContext.constants.player.minPlayerCount) {
		auto event = ShowMessagePopUpEvent("Player Count",
			"Not enough players.\n current min. Player Count: " + std::to_string(appContext.constants.player.minPlayerCount));
		appContext.eventManager.InvokeEvent(event);
		valid = false;
	}
	else if (m_players.size() > appContext.constants.player.maxPlayerCount) {
		auto event = ShowMessagePopUpEvent("Player Count",
			"Too many players.\n current max Player Count: " + std::to_string(appContext.constants.player.maxPlayerCount));
		appContext.eventManager.InvokeEvent(event);
		valid = false;
	}
	else {
		valid = true;
	}

	auto event = ValidatePlayerCountResultEvent(valid);
	appContext.eventManager.InvokeEvent(event);
}
void GameManager::ShuffleCurrentRoundPlayer() {
	std::shuffle(m_currentRoundPlayers.begin(), m_currentRoundPlayers.end(), m_random);
}

void GameManager::SendCurrentPlayerID() {
	unsigned int ID;
	std::shared_ptr<Player> player;

	if (GetCurrentPlayer(player)) {
		ID = player->GetID();
	}
	else {
		ID = 0;
	}

	auto event = UpdateCurrentPlayerIDEvent(ID);
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void GameManager::SendNextPlayerID() {
	unsigned int ID;
	std::shared_ptr<Player> player;

	if (GetNextPlayer(player)) {
		ID = player->GetID();
	}
	else {
		ID = 0;
	}

	auto event = UpdateNextPlayerIDEvent(ID);
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

// rounds
void GameManager::NextRound(bool valid) {

	if (!valid) { return; }

	AppContext& appContext = AppContext::GetInstance();
	// events and so on first

	m_startGalaxy = m_mainGalaxy;
	m_currentGalaxy = m_startGalaxy;
	m_currentRoundPlayers = m_players;

	ShuffleCurrentRoundPlayer();
	SendCurrentPlayerID();
	SendNextPlayerID();

	++appContext.constants.global.currentRound;

	appContext.eventManager.InvokeEvent(ShowNextRoundEvent());
}
void GameManager::NextTurn(bool valid) {

	if (!valid) { return; }

	m_currentRoundPlayers.pop_back();

	m_currentGalaxy = m_startGalaxy; // TODO: filter for relevant data for current player

	SendCurrentPlayerID();
	SendNextPlayerID();

	AppContext::GetInstance().eventManager.InvokeEvent(ShowNextTurnEvent());
}
void GameManager::ValidateNextTurn() {

	if (m_currentRoundPlayers.size() <= 1) { 
		auto event = ShowValidatePopUp(
			"next round?",
			"your turn will be over.",
			[this](bool valid) {
				this->NextRound(valid);
			}
		);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto event = ShowValidatePopUp(
			"next player?",
			"your turn will be over.",
			[this](bool valid) {
				this->NextTurn(valid);
			}
		);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
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

	auto updateEvent = UpdateCheckGameEventsUI(&m_gameEvents);
	AppContext::GetInstance().eventManager.InvokeEvent(updateEvent);
}

// galaxy
void GameManager::GenerateGalaxy() {
	AppContext& appContext = AppContext::GetInstance();
	Vec2<int> size = {
		appContext.constants.world.currentDimensionX,
		appContext.constants.world.currentDimensionY
	};
	auto galaxy = std::make_shared<Galaxy>(
		size,
		appContext.constants.world.currentPlanetCount,
		m_players,
		m_npcs[PlayerType::NEUTRAL]
		);

	if (galaxy->IsValid()) {
		m_mainGalaxy = galaxy;
		auto event = GalaxyGeneratedUIEvent();
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		auto event = ShowMessagePopUpEvent("Galaxy", "Unable to generate the Galaxy.\nTo many Plantes.");
		appContext.eventManager.InvokeEvent(event);
	}
}
void GameManager::GenerateShowGalaxy() {
	AppContext& appContext = AppContext::GetInstance();
	Vec2<int> size = {
		appContext.constants.world.showDimensionX,
		appContext.constants.world.showDimensionY,
	};

	auto galaxy = std::make_shared<Galaxy>(
		size,
		appContext.constants.world.showPlanetCount,
		m_players,
		m_npcs[PlayerType::NEUTRAL]
		);

	if (galaxy->IsValid()) {
		m_showGalaxy = galaxy;
		auto event = SendGalaxyPointerEvent(m_showGalaxy.get());
		appContext.eventManager.InvokeEvent(event);
	}
	else if (m_showGalaxy) {
		auto event = SendGalaxyPointerEvent(m_showGalaxy.get());
		appContext.eventManager.InvokeEvent(event);
		Print("Could not geneared ShowGalaxy -> Use old Galaxy", PrintType::EXPECTED_ERROR);
	}
	else {
		Print("Could not geneared ShowGalaxy -> No Galaxy", PrintType::ERROR);
	}
}

// Fleet
void GameManager::AddFleet(SendFleedInstructionEvent const* event) {

	if (!ValidateAddFleetInput(event)) { return; }

	std::shared_ptr<Player> currentPlayer;
	if (!GetCurrentPlayer(currentPlayer)) { popup("No current player selected."); return; }
	if (!m_mainGalaxy->AddFleet(event, currentPlayer)) { return; }

	Print("valid fleet");
}

bool GameManager::ValidateAddFleetInput(SendFleedInstructionEvent const* event) {

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

	bool doubleDestination =
		event->GetDestination() > 0
		&& (event->GetDestinationX() > 0
			|| event->GetDestinationY() > 0);
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

	// Events
	if (auto const* GameEvent = dynamic_cast<UpdateCheckGameEvent const*>(&event)) {
		SetGameEventActive(GameEvent);
		return;
	}
	if (auto const* GameEvent = dynamic_cast<InitialCheckGameEventDataEvent const*>(&event)) {
		auto updateEvent = UpdateCheckGameEventsUI(&m_gameEvents);
		AppContext::GetInstance().eventManager.InvokeEvent(updateEvent);
		return;
	}

	// Galaxy
	if (auto const* galaxyEvent = dynamic_cast<GenerateGalaxyEvent const*>(&event)) {
		GenerateGalaxy();
		return;
	}
	if (auto const* galaxyEvent = dynamic_cast<GetGalaxyPointerEvent const*>(&event)) {
		assert(m_mainGalaxy);
		auto retunEvent = SendGalaxyPointerEvent(m_mainGalaxy.get());
		AppContext::GetInstance().eventManager.InvokeEvent(retunEvent);
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
	if (auto const* fleetEvent = dynamic_cast<SendFleedInstructionEvent const*> (&event)) {
		AddFleet(fleetEvent);
		return;
	}
}
