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
#include <memory>

class GameManager final : public EventListener {
private:
	std::unordered_map<PlayerType, std::shared_ptr<Player>> m_npcs;
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<std::shared_ptr<Player>> m_currentRoundPlayers;
	std::unordered_map<GameEventType, bool> m_gameEvents;
	std::shared_ptr<Galaxy> m_mainGalaxy = nullptr; //! < contains the global galaxy with all changes.
	std::shared_ptr<Galaxy> m_startGalaxy = nullptr; //! < contains the data at round begin. every round it gets overwritten by the main galaxy
	std::shared_ptr<Galaxy> m_currentGalaxy = nullptr; //! < is used to store the player data of one player. every term it gets overwritten by the start Galaxy
	std::shared_ptr<Galaxy> m_showGalaxy = nullptr; //! < is a hardcoded galaxy that is used to garaty, that it generation is valid.

	// player
	[[nodiscard]] bool ValidAddPlayer() const;
	[[nodiscard]] unsigned int GetNextID() const;
	[[nodiscard]] bool IsExistingID(unsigned int ID) const;

	[[nodiscard]] bool GetCurrentPlayer(std::shared_ptr<Player>& currentPlayer) const;
	[[nodiscard]] bool GetNextPlayer(std::shared_ptr<Player>& nextPlayer) const;

	void AddPlayer(AddPlayerEvent const* event);
	void EditPlayer(EditPlayerEvent const* event) const;
	void DeletePlayer(DeletePlayerEvent const* event);
	void ResetPlayer();
	void CheckPlayerCount() const;

	/** send the current player ID via an event
	 *  will send 0 if no player is active
	 */
	void SendCurrentPlayerID();
	/** send the next player ID via an event
	 *  will send 0 if no next player exsits
	 */
	void SendNextPlayerID();

	// rounds
	/** next round triggers the Evaluation
	 */
	void NextRound();
	/** next term triggers the next player and changes the inforamtion that are send to UI so that only the current Player is displayed
	 */
	void NextTerm(ValidatedNextTermEvent const* event);
	void ValidateNextTerm();

	// events
	void SetGameEventActive(UpdateCheckGameEvent const* event);

	// galaxy
	void GenerateGalaxy();
	void GenerateShowGalaxy();

	// game
	void StartGame();

public:
	GameManager();

	void Update();

	void OnEvent(Event const& event) override;
};

