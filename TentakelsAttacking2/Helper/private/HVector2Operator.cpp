//
// Purpur Tentakel
// 01.12.2022
//

#include "HVector2Operator.h"
#include <cmath>

Vector2 operator+(Vector2 const& lhs, Vector2 const& rhs) {
    return {
        lhs.x + rhs.x, lhs.y + rhs.y
    };
}
Vector2 operator-(Vector2 const& lhs, Vector2 const& rhs) {
    return {
        lhs.x - rhs.x, lhs.y - rhs.y
    };
}

float LenVec2(Vector2 const& value) {
    return std::sqrt(value.x * value.x + value.y * value.y);
}
