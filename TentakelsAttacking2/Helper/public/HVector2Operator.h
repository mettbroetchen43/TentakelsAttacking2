//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "CustomRaylib.h"

/**
 * adds two Vector2 from Raylib.
 */
[[nodiscard]] Vector2 operator+ (Vector2 const& lhs, Vector2 const& rhs);
/**
 * subtracts two Vector2 from Raylib.
 */
[[nodiscard]] Vector2 operator- (Vector2 const& lhs, Vector2 const& rhs);

/**
 * returns the length of an Vector2 from Raylib.
 */
[[nodiscard]] float LenVec2(Vector2 const& value);