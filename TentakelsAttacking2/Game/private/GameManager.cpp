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
#include "SceneType.h"
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

	auto name { event->GetName() };
	auto color{ event->GetColor() };

	auto const l{ [&, name, color](bool valid) {
			if (valid) {
				StopGameEvent const eventRet{ };
				AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
				AddPlayerEvent const eventPlay{ name, color };
				this->AddPlayer(&eventPlay);
			}
		}
	};
	if (not CheckValidAddRemovePlayer(l)) { 
		return;
	}

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
		name,
		color
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

	auto id{ event->GetID() };

	auto const l{ [&, id](bool valid) {
			if (valid) {
				StopGameEvent const eventRet{ };
				AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
				DeletePlayerEvent const eventPlay{ id };
				this->DeletePlayer(&eventPlay);
			}
		}
	};
	if (not CheckValidAddRemovePlayer(l)) { 
		return;
	}

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
	auto const l{ [&](bool valid) {
			if (valid) {
				StopGameEvent const eventRet{ };
				AppContext::GetInstance().eventManager.InvokeEvent(eventRet);
				this->ResetPlayer();
			}
		}
	};
	if (not CheckValidAddRemovePlayer(l)) { 
		return;
	}

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
	if (not AppContext::GetInstance().constants.player.shuffle){ return; }

	std::shuffle(m_currentRoundPlayers.begin(), m_currentRoundPlayers.end(), m_random);
	
	Print(
		PrintType::ONLY_DEBUG,
		"player shuffled"
	);
}
bool GameManager::CheckValidAddRemovePlayer(std::function<void(bool valid)> forPopup) const {
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	if (appContext.constants.global.isGameRunning) {
		ShowValidatePopUp const event{
			"Game is running",
			"not able zu add or remove any player. Stop the current game?",
			forPopup
		};
		appContext.eventManager.InvokeEvent(event);
		return false;
	}
	return true;
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
	appContext.constants.global.isGameSaved = false;
	// events and so on first
	Update();

	m_currentRoundPlayers = m_players;
	ShuffleCurrentRoundPlayer();

	m_galaxyManager.CopyGalaxies(CopyGalaxyType::COPY_ALL);

	SendCurrentPlayerID();
	SendNextPlayerID();

	++appContext.constants.global.currentRound;

	Player_ty player { } ;
	if (not GetCurrentPlayer(player)) {
		Print(
			PrintType::ONLY_DEBUG,
			"next round started -> can't get current player"
		);
	}
	else {
		Print(
			PrintType::ONLY_DEBUG,
			"next round started -> player {}",
			player->GetID()
		);
	}

	appContext.eventManager.InvokeEvent(ShowNextRoundEvent());
}
void GameManager::NextTurn(bool valid) {


	if (!valid) { return; }

	AppContext_ty appContext{ AppContext::GetInstance() };
	appContext.constants.global.isGameSaved = false;
	m_currentRoundPlayers.pop_back();

	m_galaxyManager.CopyGalaxies(CopyGalaxyType::COPY_START);


	SendCurrentPlayerID();
	SendNextPlayerID();

	Player_ty player { };
	if (not GetCurrentPlayer(player)) {
		Print(
			PrintType::ONLY_DEBUG,
			"next turn started -> can't get current player"
		);
	}
	else{
		Print(
			PrintType::ONLY_DEBUG,
			"next turn started -> player {}",
			player->GetID()
		);
	}

	AppContext::GetInstance().eventManager.InvokeEvent(ShowNextTurnEvent());
}
void GameManager::ValidateNextTurn() {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	if (m_currentRoundPlayers.size() <= 1) {
		ShowValidatePopUp const event{
			appContext.languageManager.Text("logic_game_manager_popup_next_round_title", "?"),
			appContext.languageManager.Text("logic_game_manager_popup_next_round_text"),
			[this](bool valid) {
				this->NextRound(valid);
			}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		ShowValidatePopUp const event{
			appContext.languageManager.Text("logic_game_manager_popup_next_turn_title", "?"),
			appContext.languageManager.Text("logic_game_manager_popup_next_turn_text"),
			[this](bool valid) {
				this->NextTurn(valid);
			}
		};
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
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
		if ((event->GetDestinationX() < 0) || (event->GetDestinationY() < 0)) {
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
		&& (event->GetDestinationX() >= 0
			|| event->GetDestinationY() >= 0) };
	if (doubleDestination) {
		popup("to many inputs for destination");
		return false;
	}

	return true;
}

// game
void GameManager::StartGame() {
	AppContext_ty appContext{ AppContext::GetInstance() };

	if (appContext.constants.global.isGameRunning and not appContext.constants.global.isGameSaved) {
		ShowValidatePopUp  const event {
			appContext.languageManager.Text("ui_popup_game_still_running_title"),
			appContext.languageManager.Text("ui_popup_game_still_running_subtitle", '\n'),
			[this](bool valid){
				if (valid){
					this->StopGame();
					this->StartGame();
				}
			}
		};
		appContext.eventManager.InvokeEvent(event);
		return;
	}

	m_currentRoundPlayers = m_players;

	ShuffleCurrentRoundPlayer();
	SendCurrentPlayerID();
	SendNextPlayerID();

	appContext.constants.global.currentRound  = 0    ;
	appContext.constants.global.isGameRunning = true ;
	appContext.constants.global.isGamePaused  = false;
	appContext.constants.global.isGameSaved   = false;

	Player_ty player { };
	if (not GetCurrentPlayer(player)) {
		Print(
			PrintType::ONLY_DEBUG,
			"game started -> can't get current player"
		);
	}

	Print(
		PrintType::ONLY_DEBUG,
		"game started -> player {}",
		player->GetID()
	);
	SwitchSceneEvent const event{ SceneType::MAIN };
	appContext.eventManager.InvokeEvent(event);
}
void GameManager::StopGame() {
	AppContext_ty appConstants{ AppContext::GetInstance() };
	appConstants.constants.global.isGameRunning = false;
	appConstants.constants.global.isGamePaused = true;
	Print(
		PrintType::ONLY_DEBUG,
		"game stopped and paused"
	);
}
void GameManager::PauseGame() {
	AppContext_ty appContext{ AppContext::GetInstance() };
	appContext.constants.global.isGamePaused = true;
	Print(
		PrintType::ONLY_DEBUG,
		"game paused"
	);
}
void GameManager::ResumeGame() {
	AppContext_ty appContext{ AppContext::GetInstance() };
	if (not appContext.constants.global.isGameRunning){
		ShowMessagePopUpEvent const event {
			appContext.languageManager.Text("ui_popup_no_game_title"),
			appContext.languageManager.Text("ui_popup_no_game_subtitle"),
			[](){}
		};
		appContext.eventManager.InvokeEvent(event);
		Print(
			PrintType::ONLY_DEBUG,
			"not able to resume to game because its no game running"
		);
		return;
	}
	appContext.constants.global.isGamePaused = false;
	Print(
		PrintType::ONLY_DEBUG,
		"resumed to game"
	);
	SwitchSceneEvent const event{ SceneType::MAIN };
	appContext.eventManager.InvokeEvent(event);
}
void GameManager::QuitGame() {
	AppContext_ty appContext{ AppContext::GetInstance() };
	if (not appContext.constants.global.isGameSaved){
		ShowValidatePopUp const event{
			appContext.languageManager.Text("ui_popup_not_saved_title"),
			appContext.languageManager.Text("ui_popup_not_saved_subtitle", '\n'),
			[this](bool valid){
				if (valid){
					AppContext_ty appContext{ AppContext::GetInstance() };
					appContext.constants.global.isGameSaved = true;
					this->QuitGame();
				}
			}
		};
		appContext.eventManager.InvokeEvent(event);
		return;
	}

	CloseWindowEvent const event{ };
	appContext.eventManager.InvokeEvent(event);
}

GameManager::GameManager()
	: m_galaxyManager{ this } {

	AppContext::GetInstance().eventManager.AddListener(this);
	m_npcs[PlayerType::NEUTRAL] = std::make_shared<Player>(100, PlayerType::NEUTRAL);

	Print(PrintType::INITIALIZE, "GameManager");
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
	if (auto const* gameEvent = dynamic_cast<StopGameEvent const*> (&event)) {
		StopGame();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<PauseGameEvent const*> (&event)) {
		PauseGame();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<ResumeGameEvent const*> (&event)) {
		ResumeGame();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<QuitGameEvent const*> (&event)) {
		QuitGame();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<TriggerNextTurnEvent const*> (&event)) {
		ValidateNextTurn();
		return;
	}
	if (auto const* gameEvent = dynamic_cast<GetUpdateEvaluation const*> (&event)) {
		AppContext::GetInstance().eventManager.InvokeEvent(SendUpdateEvaluation{ 
			m_lastUpdateResults.first ,m_lastUpdateResults.second});
		return;
	}

	// Fleet
	if (auto const* fleetEvent = dynamic_cast<SendFleetInstructionEvent const*> (&event)) {
		AddFleet(fleetEvent);
		return;
	}
}
