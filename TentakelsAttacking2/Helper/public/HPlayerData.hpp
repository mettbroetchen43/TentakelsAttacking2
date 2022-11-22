//
// Purpur Tentakel
// 19.10.2022
//

#pragma once
#include <raylib.h>
#include <string>

struct PlayerData final {
	unsigned int ID = 0;
	std::string name = "";
	Color color = WHITE;

	PlayerData(unsigned int _ID, std::string _name, Color _color)
		: ID(_ID), name(_name), color(_color) { }
	PlayerData() = default;
};

[[nodiscard]] inline bool StortPlayerByID_ASC(
	PlayerData const& lhs, PlayerData const& rhs) {
	return lhs.ID < rhs.ID;
}
[[nodiscard]] inline bool StortPlayerByID_DSC(
	PlayerData const& lhs, PlayerData const& rhs) {
	return lhs.ID > rhs.ID;
}

[[nodiscard]] inline bool operator==(
	PlayerData const& lhs, PlayerData const& rhs) {
	return lhs.ID == rhs.ID;
}
[[nodiscard]] inline bool operator!=(
	PlayerData const& lhs, PlayerData const& rhs) {
	return !(lhs == rhs);
}
