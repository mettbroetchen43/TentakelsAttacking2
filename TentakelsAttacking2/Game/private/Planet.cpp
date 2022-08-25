//
// PurpurTentakel
// 10.08.22
//

#include "Planet.h"
#include "Player.h"

Planet::Planet(int id, double x, double y, int ships, std::weak_ptr<Player> player, int production)
	:SpaceObject(id,x,y,ships,player),m_production(production),m_maxShips(300) {}

void Planet::PreUpdate(Galaxy const& gameManager) {
}

void Planet::Update(Galaxy const& gameManager) {
	ProduceShips();
}

void Planet::PostUpdate(Galaxy const& gameManager) {
}

std::string Planet::ToString() const {
	return "Planet // " + std::to_string(m_id) + " // " + m_position.ToString();
}

void Planet::ProduceShips() {
	m_ships += m_production;
	ResetMaxShips();
}

void Planet::ResetMaxShips() {
	if (player.lock()->IsHumanPlayer()) {
		return;
	}
	if (m_ships > m_maxShips) {
		m_ships = static_cast<int>(m_maxShips);
	}
}
