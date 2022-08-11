//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "Player.h"
#include "Galaxy.h"
#include <vector>

class GameManager {
private:
	std::vector<std::shared_ptr<Player>> m_players;
	Galaxy m_galaxy;
public:
	[[nodiscard]] std::vector<std::shared_ptr<Player>>& GetPlayers();
	[[nodiscard]] std::vector<std::shared_ptr<Player>> const& GetPlayers() const;

	void Update();
};

