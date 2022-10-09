//
// Purpur Tentakel
// 30.09.22
//

#include "EmptyCell.h"

Vector2 const& EmptyCell::GetNeededSize() const {
	return { 0.05f,0.05f };
}

void EmptyCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Cell::CheckAndUpdate(mousePosition, appContext);
}
