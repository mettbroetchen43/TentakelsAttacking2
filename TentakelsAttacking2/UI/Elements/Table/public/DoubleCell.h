//
// Purpur Tentakel
// 02.10.2022
//

#pragma once
#include "Cell.h"

class DoubleCell : public Cell {
public:
	double value;

	using Cell::Cell;

	[[nodiscard]] Vector2 GetNeededSize() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext) override;
};