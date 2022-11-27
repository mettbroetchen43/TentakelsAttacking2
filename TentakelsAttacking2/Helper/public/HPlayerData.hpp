//
// Purpur Tentakel
// 19.10.2022
//

#pragma once
#include <raylib.h>
#include <string>

/**
 * contans all non logic player data
 */
struct PlayerData final {
	unsigned int ID = 0; ///< contans the id -> matches the id in the logic
	std::string name = ""; ///< contains the name
	Color color = WHITE; ///< contains the color
};

/**
 * returns if player lhs has a smaler id than player rhs.
 */
[[nodiscard]] inline bool StortPlayerByID_ASC(
	PlayerData const& lhs, PlayerData const& rhs) {
	return lhs.ID < rhs.ID;
}
/**
 * returns if player lhs has a heigher id than player rhs.
 */
[[nodiscard]] inline bool StortPlayerByID_DSC(
	PlayerData const& lhs, PlayerData const& rhs) {
	return lhs.ID > rhs.ID;
}

/**
 * checks if two players are equal by id.
 */
[[nodiscard]] inline bool operator==(
	PlayerData const& lhs, PlayerData const& rhs) {
	return lhs.ID == rhs.ID;
}
/**
 * checks if two player are unequal by id.
 */
[[nodiscard]] inline bool operator!=(
	PlayerData const& lhs, PlayerData const& rhs) {
	return !(lhs == rhs);
}
