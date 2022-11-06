//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "Player.h"
#include "EventListener.hpp"
#include "UIEvents.hpp"
#include "GenerelEvents.hpp"
#include "GameEventTypes.hpp"
#include <vector>

class GameManager final : public EventListener {
private:
	std::vector<std::shared_ptr<Player>> m_players;
	std::unordered_map<GameEventType, bool> m_gameEvents;

	// player
	[[nodiscard]] bool ValidAddPlayer() const;
	[[nodiscard]] unsigned int GetNextID() const;
	[[nodiscard]] bool IsExistingID(unsigned int ID) const;

	void AddPlayer(AddPlayerEvent const* event);
	void EditPlayer(EditPlayerEvent const* event) const;
	void DeletePlayer(DeletePlayerEvent const* event);
	void ResetPlayer();
	void CheckPlayerCount() const;

	// events
	void SetGameEventActive(UpdateCheckGameEvent const* event);

public:
	GameManager();

	void Update();

	void OnEvent(Event const& event) override;
};

