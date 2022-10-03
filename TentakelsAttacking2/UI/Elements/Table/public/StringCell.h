//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "Cell.h"

class StringCell : public Cell {
private:
protected:
public:
	std::string value;

	using Cell::Cell;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};

