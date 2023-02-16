//
// Purpur Tentakel
// 07.11.2022
//

#pragma once
#include "SpaceObject.h"

/**
 * the planet ia a space object.
 */
class Planet final : public SpaceObject {
private:
	using vec2pos = Vec2<int>; ///< the type of the position
	bool m_isHomePlanet; ///< contains if this planet is a home planet
	bool m_isDestroyed = false; ///< contains if the planet is destroyed
	int m_planetNumber; ///< contains the planet number
	size_t m_maxShips; ///< contains the max amount of ships the planet can hold by non hunman playern
	size_t m_production; ///< contains the production hat gets add every round

public:
	/**
	 * ctor.
	 * initialize all values.
	 */
	Planet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player,
		bool isHomePlanet, int m_planetNumber);

	/**
	 * retuns if the planet is a home planet.
	 */
	[[nodiscard]] bool IsHomePlanet() const;

	/**
	 * returns if the current spaceobject is a planet.
	 */
	[[nodiscard]] bool IsPlanet() const override;

	/**
	 * sets if the planet is destroyed.
	 */
	void SetIsDestroyed(bool isDestroyed);
	/**
	 * returns if the planet is destroyed.
	 */
	[[nodiscard]] bool IsDestroyed() const;
};
