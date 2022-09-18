//
// Purpur Tentakel
// 18.09.2022
//

#pragma once
#include <raylib.h>

enum class Alignment {
	TOP_LEFT,
	TOP_MID,
	TOP_RIGHT,
	MID_LEFT,
	MID_MID,
	MID_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_MID,
	BOTTOM_RIGHT,
	DEFAULT,
};

[[nodiscard]] Rectangle GetAlignedCollider(Vector2& pos, Vector2 size,
	Alignment allignment, Vector2 resolution);
