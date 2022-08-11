//
// PurpurTentakel
// 10.08.22
//

#include "GameManager.h"

std::vector<std::shared_ptr<Player>>& GameManager::GetPlayers() {
	return m_players;
}
std::vector<std::shared_ptr<Player>> const& GameManager::GetPlayers() const {
	return m_players;
}

void GameManager::Update() {
	m_galaxy.PreUpdate(); // bevor main update -> z.B. move
	m_galaxy.Update();  // main update
	m_galaxy.PostUpdate(); // debug Print
}
