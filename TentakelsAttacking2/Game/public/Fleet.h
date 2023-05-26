//
// PurpurTentakel
// 16.02.22
//

#pragma once
#include "SpaceObject.h"

class Fleet final : public SpaceObject {
private:
	SpaceObject_ty m_target;

public:
	/**
	 * ctor without ships.
	 * only initialization
	 */
	Fleet(unsigned int ID, vec2pos_ty position, Player_ty player, SpaceObject_ty target);
	/**
	 * ctor.
	 * only initialization.
	 */
	Fleet(unsigned int ID, vec2pos_ty position, size_t ships, Player_ty player, SpaceObject_ty target);

	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] bool IsFleet() const override;

	/**
	 * returns the target of the fleet.
	 */
	[[nodiscard]] SpaceObject_ty GetTarget() const;

	/**
	 * moves the fleet to the target.
	 */
	void Update(Galaxy_ty_raw galaxy) override;
};
