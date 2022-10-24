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
enum class TextAlignment {
	TOP,
	MID,
	BOTTOM,
	LEFT,
	RIGHT,
};

Rectangle GetAlignedCollider(Vector2& pos, Vector2 size,
	Alignment allignment, Vector2 resolution);

[[nodiscard]] TextAlignment GetHorisontalTextAlignment(Alignment alignment);
[[nodiscard]] TextAlignment GetVerticalTextAlignment(Alignment alignment);
