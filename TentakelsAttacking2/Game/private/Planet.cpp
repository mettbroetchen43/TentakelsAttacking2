//
// Purpur Tentakel
// 07.11.2022
//

#include "Planet.h"
#include "HRandom.h"
#include "AppContext.h"
#include "Player.h"

Planet::Planet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player,
	bool isHomePlanet, int planetNumber)
	: SpaceObject{ ID, position, player }, m_isHomePlanet{ isHomePlanet },
	m_planetNumber{ planetNumber } {

	AppContext& appContext{ AppContext::GetInstance() };
	m_maxShips = appContext.constants.planet.maxShips;

	if (m_isHomePlanet) {
		m_production = appContext.constants.planet.homeworldProduction;
		m_ships = m_production * appContext.constants.planet.startingHumanShipsMultiplicator;
	}
	else {
		Random& random{ Random::GetInstance() };
		size_t const r{ static_cast<size_t>(random.random(
			appContext.constants.planet.maxProduction -
			appContext.constants.planet.minProduction
		)) };
		m_production = r + appContext.constants.planet.minProduction;
		m_ships = m_production * appContext.constants.planet.startingGlobalShipsMultiplicator;
	}
}

bool Planet::IsHomePlanet() const {
	return m_isHomePlanet;
}

bool Planet::IsPlanet() const {
	return true;
}

size_t Planet::GetProduction() const {
	return m_production;
}

void Planet::SetDestroyed(bool isDestroyed) {
	m_isDestroyed = isDestroyed;
}
bool Planet::IsDestroyed() const {
	return m_isDestroyed;
}

void Planet::SetDescovered(bool isDescovered) {
	m_isDescovered = isDescovered;
}

bool Planet::IsDescovered() const {
	return m_isDescovered;
}
