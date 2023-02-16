//
// PurpurTentakel
// 16.02.22
//

#pragma once
#include "SpaceObject.h"

class Fleet : public SpaceObject {
private:
	std::shared_ptr<SpaceObject> m_target;

public:
	/**
	 * ctor without ships.
	 * only initialisation
	 */
	Fleet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player, std::shared_ptr<SpaceObject> target);
	/**
	 * ctor.
	 * only initialisation.
	 */
	Fleet(unsigned int ID, vec2pos position, size_t ships, std::shared_ptr<Player> player, std::shared_ptr<SpaceObject> target);

	/**
	 * returns if the current spaceobject is a planet.
	 */
	[[nodiscard]] bool IsFleet() const override;
};