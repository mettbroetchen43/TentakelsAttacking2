//
// Purpur Tentakel
// 30.09.22
//

#pragma once
#include "AbstractTableCell.h"

/**
 * provides an empty cell for the table class.
 */
class EmptyCell final : public AbstractTableCell {
private:
	///< no values becaus its an emoty cell

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	EmptyCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution);

	/**
	 * returns the size the cell needs to display the "value" perfectly.
	 * returns in this case always 0.5f,0.5f because no value is existing.
	 */
	[[nodiscard]] Vector2 GetNeededSize() override;

	/**
	 * no function because nothing to update here.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the cell.
	 */
	void Render(AppContext const& appContext) override;
};