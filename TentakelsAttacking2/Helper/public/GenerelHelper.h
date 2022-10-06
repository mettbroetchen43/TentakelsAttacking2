//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include <raylib.h>

// Colors
[[nodiscard]] bool operator==(Color lhs, Color rhs);
[[nodiscard]] bool operator!=(Color lhs, Color rhs);

// Position
Vector2 GetElementPosition(Vector2 const& pos, Vector2 const& size,
	float x, float y);
Vector2 GetElementSize(Vector2 const& size, float x, float y);

// Index
size_t GetIndexFromRowAndColumn(size_t row, size_t column, size_t maxColumn);
