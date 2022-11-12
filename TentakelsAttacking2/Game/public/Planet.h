//
// Purpur Tentakel
// 07.11.2022
//

#pragma once
#include "SpaceObject.h"

class Planet final : public SpaceObject {
private:
	using vec2pos = Vec2<size_t>;
	bool m_isHomePlanet;
	bool m_isDestroyed = false;
	int m_planetNumber;
	size_t m_maxShips; // set from config
	size_t m_production; // set from config

public:
	Planet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player,
		bool isHomePlanet, int m_planetNumber);

	[[nodiscard]] bool IsHomePlanet() const;

	void SetIsDestroyed(bool isDestroyed);
	[[nodiscard]] bool IsDestroyed() const;
};
