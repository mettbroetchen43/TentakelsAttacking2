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
	bool m_isHomePlanet{ }; ///< contains if this planet is a home planet
	bool m_isDestroyed{ false }; ///< contains if the planet is destroyed
	bool m_isDiscovered{ false }; ///< contains if any player has discovered this planet
	int m_planetNumber; ///< contains the planet number
	size_t m_maxShips; ///< contains the max amount of ships the planet can hold by non human players
	size_t m_production; ///< contains the production hat gets add every round

public:
	/**
	 * ctor.
	 * initialize all values.
	 */
	Planet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player,
		bool isHomePlanet, int m_planetNumber);

	/**
	 * returns if the planet is a home planet.
	 */
	[[nodiscard]] bool IsHomePlanet() const;

	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] bool IsPlanet() const override;

	/**
	 * returns the production count.
	 */
	[[nodiscard]] size_t GetProduction() const;

	/**
	 * sets if the planet is destroyed.
	 */
	void SetDestroyed(bool isDestroyed);
	/**
	 * returns if the planet is destroyed.
	 */
	[[nodiscard]] bool IsDestroyed() const;
	/**
	 * set if the planet is discovered.
	 */
	void SetDiscovered(bool isDescovered);
	/**
	 * returns if the planet is discovered from any player.
	 */
	[[nodiscard]] bool IsDiscovered() const;

	/**
	 * products ships.
	 */
	void Update() override;
};
