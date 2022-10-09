//
// Purpur Tentakel
// 30.09.22
//

#pragma once
#include "Cell.h"

class EmptyCell : public Cell {
private:

protected:

public:
	using Cell::Cell;

	[[nodiscard]] Vector2 const& GetNeededSize() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
};