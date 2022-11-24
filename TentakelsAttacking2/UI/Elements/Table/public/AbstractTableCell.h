//
// Purpur Tentakel
// 17.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"

/**
 * provides a basic cell for the table class where all table cells will hesitate from.
 */
class AbstractTableCell : public UIElement, public Focusable {
protected:
	bool m_editable = true; ///< contains if the cell is editable

	/**
	 * checks if the cell schould resize and calls so if it should.
	 */
	void CheckResizeCells(Vector2 resolution,
		AppContext const& appContext, bool resize);

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	AbstractTableCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution);
	/**
	 * virtual dtor.
	 */
	virtual ~AbstractTableCell() = default;

	/**
	 * returns the size the cell would need to display the value perfectly.
	 */
	[[nodiscard]] virtual Vector2 GetNeededSize() = 0 ;

	/**
	 * sets if the sell is editable.
	 */
	void SetEditable(bool editable);
	/**
	 * returns if the cell is editable.
	 */
	[[nodiscard]] bool IsEnabled() const override;

	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const;

	/**
	 * sets a new pos.x ans resizes cell.
	 */
	void SetPosX(float posX, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
	/**
	 * sets a new pos.y ans resizes cell.
	 */
	void SetPosY(float posY, Vector2 resolution,
		AppContext const& appContext, bool resize = true);

	/**
	 * sets a new size.x ans resizes cell.
	 */
	void SetSizeX(float sizeX, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
	/**
	 * sets a new size.y ans resizes cell.
	 */
	void SetSizeY(float sizeY, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
};
