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

class GameManager : public EventListener {
private:
	std::vector<std::shared_ptr<Player>> m_players;
	std::unordered_map<GameEventType, bool> m_gameEvents;
	Galaxy m_galaxy;

	[[nodiscard]] bool ValidAddPlayer() const;
	[[nodiscard]] unsigned int GetNextID() const;
	[[nodiscard]] bool IsExistingID(unsigned int ID) const;

	void AddPlayer(AddPlayerEvent const* event);
	void EditPlayer(EditPlayerEvent const* event) const;
	void DeletePlayer(DeletePlayerEvent const* event);
	void CheckPlayerCount() const;

	void SetGameEventActive(UpdateCheckGameEvent const* event);

public:
	GameManager();

	[[nodiscard]] std::vector<std::shared_ptr<Player>>& GetPlayers();
	[[nodiscard]] std::vector<std::shared_ptr<Player>> const& GetPlayers() const;

	void Update();

	void OnEvent(Event const& event) override;
};

