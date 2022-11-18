//
// Purpur Tentakel
// 30.09.22
//

#pragma once
#include "AbstractTableCell.h"

class EmptyCell final : public AbstractTableCell {
private:

public:
	EmptyCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution);

	[[nodiscard]] Vector2 GetNeededSize() override;

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};