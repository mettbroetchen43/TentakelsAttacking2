//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "Player.h"
#include "Galaxy.h"
#include "EventListener.hpp"
#include "UIEvents.hpp"
#include "GenerelEvents.hpp"
#include "GameEventTypes.hpp"
#include <vector>
#include <random>
#include <memory>

/**
 * manage the hole game.
 * that contains players, npcs, game events, galaxy, event communivation with the ui.
 */
class GameManager final : public EventListener {
private:
	std::default_random_engine m_random = std::default_random_engine(); ///< contains a random engine to shuffle the player each round
	std::unordered_map<PlayerType, std::shared_ptr<Player>> m_npcs; ///< contains all npcs to seperaste them from the player
	std::vector<std::shared_ptr<Player>> m_players; ///< contains all player -> this is the main player vector
	std::vector<std::shared_ptr<Player>> m_currentRoundPlayers; ///< contains the remaining player of the current round
	std::unordered_map<GameEventType, bool> m_gameEvents; ///< contains whether the game Events are active or not
	std::shared_ptr<Galaxy> m_mainGalaxy = nullptr; ///< contains the global galaxy with all changes.
	std::shared_ptr<Galaxy> m_startGalaxy = nullptr; ///< contains the data at round begin. every round it gets overwritten by the main galaxy
	std::shared_ptr<Galaxy> m_currentGalaxy = nullptr; ///< is used to store the player data of one player. every turn it gets overwritten by the start Galaxy
	std::shared_ptr<Galaxy> m_showGalaxy = nullptr; ///< is a hardcoded galaxy that is used to garaty, that it generation is valid.

	// player
	/**
	 * validates if its valid to add an other player.
	 * returns a bool.
	 */
	[[nodiscard]] bool ValidAddPlayer() const;
	/**
	 * returns the next free player ID that is nearest to 0.
	 */
	[[nodiscard]] unsigned int GetNextPlayerID() const;
	/**
	 * returns if the curent ID is already existing.
	 */
	[[nodiscard]] bool IsExistingPlayerID(unsigned int ID) const;

	/**
	 * set the next current player.
	 * returns a bool to prove if its valid.
	 */
	[[nodiscard]] bool SetCurrentPlayer(std::shared_ptr<Player>& currentPlayer) const;
	/**
	 * set the next next player.
	 * returns a bool to prove if its valid.
	 */
	[[nodiscard]] bool SetNextPlayer(std::shared_ptr<Player>& nextPlayer) const;

	/**
	 * adds a new player.
	 * validates the new player bevor adding.
	 * opens a popup and returns if not.
	 * creates new Player id.
	 * calls the ui via event to add it too.
	 */
	void AddPlayer(AddPlayerEvent const* event);
	/**
	 * edit a player by id.
	 * checks if id exists.
	 * opens a popup and returns if not.
	 * calls the ui via event to edits it too.
	 */
	void EditPlayer(EditPlayerEvent const* event) const;
	/**
	 * deletes a player by id.
	 * checks if id exists.
	 * opens a popup and returns if not.
	 * calls the ui via event to delete it too.
	 */
	void DeletePlayer(DeletePlayerEvent const* event);
	/**
	 * delets all player.
	 * calls the ui via event to delete it too.
	 */
	void ResetPlayer();
	/**
	 * checks if the player count is valid.
	 * sends the result via event into the ui.
	 */
	void CheckPlayerCount() const;
	/**
	 * shuffles the current player.
	 * use this an the round start to get some variation every round.
	 */
	void ShuffleCurrentRoundPlayer();

	/** send the current player ID via an event
	 *  will send 0 if no player is active
	 */
	void SendCurrentPlayerID();
	/** send the next player ID via an event
	 *  will send 0 if no next player exsits
	 */
	void SendNextPlayerID();

	// rounds
	/** 
	 * next round triggers the Evaluation
	 */
	void NextRound(bool valid);
	/** 
	 * next turn triggers the next player and changes the inforamtion that are send to ui 
	 * so that only the current Player is displayed
	 */
	void NextTurn(bool valid);
	/**
	 * gets called from TriggerNextTurnEvent
	 * calls an Popup if the to validate if the currnt turn should really be over
	 * PopUp automactily calls the provided function
	 */
	void ValidateNextTurn();

	// events
	/**
	 * updates if the game events are enabled.
	 * calls the ui via event to update.
	 */
	void SetGameEventActive(UpdateCheckGameEvent const* event);

	// galaxy
	/**
	 * generates a new galaxy.
	 * if the new galaxy is valid the old galaxy gets overrite and informs the ui via event. 
	 * if not the old galaxy will be keep and generates an faliure popup.
	 */
	void GenerateGalaxy();
	/**
	 * generates a new show galaxy.
	 * if the new galaxy is valid the old galaxy gets overrite and sends a galaxy* via event to the ui.
	 * if not and an old galaxy exists, the old galaxy will be keep and will be providet via event to the ui.
	 * also prints a log entry to the console.
	 * if not and no galaxy exsitst it only prints a log entry to the console.
	 */
	void GenerateShowGalaxy();

	// fleet
	/**
	 * validates the data from the UI.
	 * generates Popups if needed.
	 */
	bool ValidateAddFleet(SendFleedInstructionEvent const* event);
	/**
	 * calls validation
	 * add new fleet.
	 */
	void AddFleet(SendFleedInstructionEvent const* event);

	// game
	/**
	 * initializes a new game after everythis is set up
	 */
	void StartGame();

public:
	/**
	 * default ctor.
	 * sets all game events to true.
	 * prints a initialize to the console.
	 */
	GameManager();

	/**
	 * TODO:: Will update the logic if a round is over.
	 * like moving etc.
	 */
	void Update();

	/**
	 * receives the incomming events and calls the correct functions.
	 */
	void OnEvent(Event const& event) override;
};

