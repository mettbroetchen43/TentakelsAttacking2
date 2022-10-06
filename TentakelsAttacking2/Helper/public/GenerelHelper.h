//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include <raylib.h>

// Colors
[[nodiscard]] bool operator==(Color lhs, Color rhs) {
	bool sameColor =
		lhs.a == rhs.a
		&& lhs.b == rhs.b
		&& lhs.g == rhs.g
		&& lhs.r == rhs.r;

	return sameColor;
}

// Position
Vector2 GetElementPosition(Vector2 const& pos, Vector2 const& size, float x, float y) {
	return {
		pos.x + x * size.x,
		pos.y + y * size.y
	};
}
Vector2 GetElementSize(Vector2 const& size, float x, float y) {
	return {
		x * size.x,
		y * size.y
	};
}

// Index
size_t GetIndexFromRowAndColumn(size_t row, size_t column, size_t maxColumn) {
	return row * maxColumn + column;
}
