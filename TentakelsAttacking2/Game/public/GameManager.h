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
#include <vector>

class GameManager : public EventListener {
private:
	std::vector<std::shared_ptr<Player>> m_players;
	Galaxy m_galaxy;

	[[nodiscard]] bool ValidAddPlayer() const;
	[[nodiscard]] bool GetNextID() const;

public:
	GameManager();

	void AddPlayer(AddPlayerEvent const* event);

	[[nodiscard]] std::vector<std::shared_ptr<Player>>& GetPlayers();
	[[nodiscard]] std::vector<std::shared_ptr<Player>> const& GetPlayers() const;

	void Update();

	void OnEvent(Event const& event) override;
};

