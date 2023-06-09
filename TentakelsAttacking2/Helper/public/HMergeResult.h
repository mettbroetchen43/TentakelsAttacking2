//
// Purpur Tentakel
// 09.06.2023
//

#pragma once
#include "HLogicAlias.hpp"

struct HMergeResult final {
	HMergeResult(Player_ty player, SpaceObject_ty origin, SpaceObject_ty destination, int count);

	[[nodiscard]] Player_ty GetPlayer() const;
	[[nodiscard]] SpaceObject_ty GetOrigin() const;
	[[nodiscard]] SpaceObject_ty GetDestination() const;
	[[nodiscard]] int GetCount() const;

private:
	Player_ty m_player;
	SpaceObject_ty m_origin;
	SpaceObject_ty m_destination;
	int m_count;
};
