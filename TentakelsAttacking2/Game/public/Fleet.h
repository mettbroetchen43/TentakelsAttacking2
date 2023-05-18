//
// PurpurTentakel
// 16.02.22
//

#pragma once
#include "SpaceObject.h"

class Fleet final : public SpaceObject {
private:
	std::shared_ptr<SpaceObject> m_target{ nullptr };

public:
	/**
	 * ctor without ships.
	 * only initialization
	 */
	Fleet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player, std::shared_ptr<SpaceObject> target);
	/**
	 * ctor.
	 * only initialization.
	 */
	Fleet(unsigned int ID, vec2pos position, size_t ships, std::shared_ptr<Player> player,
		std::shared_ptr<SpaceObject> target);

	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] bool IsFleet() const override;

	/**
	 * returns the target of the fleet.
	 */
	[[nodiscard]] SpaceObject const* GetTarget() const;
};