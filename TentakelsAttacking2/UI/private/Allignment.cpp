//
// Purpur Tentakel
// 18.09.2022
//

#include "Allignment.h"

Rectangle GetAlignedCollider(Vector2& pos, Vector2 size, Alignment allignment, Vector2 resolution) {
	switch (allignment) {
	case Alignment::TOP_LEFT:
	case Alignment::DEFAULT:
	default:
		// no adjustment of x necessary
		// no adjustment of y necessary
		break;
	case Alignment::TOP_MID:
		pos.x -= size.x / 2;
		// no adjustment of y necessary
		break;
	case Alignment::TOP_RIGHT:
		pos.x -= size.x;
		// no adjustment of y necessary
		break;
	case Alignment::MID_LEFT:
		// no adjustment of x necessary
		pos.y -= size.y / 2;
		break;
	case Alignment::MID_MID:
		pos.x -= size.x / 2;
		pos.y -= size.y / 2;
		break;
	case Alignment::MID_RIGHT:
		pos.x -= size.x;
		pos.y -= size.y / 2;
		break;
	case Alignment::BOTTOM_LEFT:
		// no adjustment of x necessary
		pos.y -= size.y;
		break;
	case Alignment::BOTTOM_MID:
		pos.x -= size.x / 2;
		pos.y -= size.y;
		break;
	case Alignment::BOTTOM_RIGHT:
		pos.x -= size.x;
		pos.y -= size.y;
		break;

	}
	Rectangle toReturn = {
		resolution.x * pos.x,
		resolution.y * pos.y,
		resolution.x * size.x,
		resolution.y * size.y
	};
	return toReturn;
}
