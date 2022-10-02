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

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
};