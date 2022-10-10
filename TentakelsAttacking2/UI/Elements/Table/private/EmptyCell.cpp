//
// Purpur Tentakel
// 30.09.22
//

#include "EmptyCell.h"

Vector2 EmptyCell::GetNeededSize() const {
	Vector2 neededSize = { 0.05f,0.05f };
	ClampNeededSize(neededSize);
	return neededSize;
}

void EmptyCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Cell::CheckAndUpdate(mousePosition, appContext);
}
