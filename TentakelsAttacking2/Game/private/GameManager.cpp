//
// PurpurTentakel
// 10.08.22
//

#include "GameManager.h"

std::vector<std::unique_ptr<Player>>& GameManager::GetPlayers() {
	return m_players;
}
std::vector<std::unique_ptr<Player>> const& GameManager::GetPlayers() const {
	return m_players;
}
