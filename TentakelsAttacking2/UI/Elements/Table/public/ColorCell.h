//
// Purpur Tentakel
// 02.10.2022
//

#pragma once
#include "Cell.h"

class ColorCell : public Cell {
public:
	Color value;

	using Cell::Cell;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext) override;
};