//
// Purpur Tentakel
// 03.04.2023
//

#include "UIElement.hpp"
#include "Focusable.h"
#pragma once

class AbstactTableCell2 : public UIElement, public Focusable {
private:
	bool m_isEditable = true; ///< contains if the cell is currently editable
	float m_textSize; ///< contains the text size the text is renderd with
	Vector2 m_textPosition; ///< contains the absolute text position 

	/**
	 * calculates a new text size from the collider.
	 */
	void CalculateTextSize();

public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	AbstactTableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID);

	/**
	 * sets if the cell is editable.
	 */
	void SetEditable(bool IsEditable) noexcept;
	/**
	 * returns true if the cell is editable.
	 */
	[[nodiscard]] bool IsEditable() const noexcept;

	/**
	 * returns if the current elements is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const noexcept override;
	/**
	 * returns thr current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const noexcept override;

	/**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the cell.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext const&) override;
	/**
	 * renders the cell
	 */
	void Render(AppContext const& appContext) override;
};