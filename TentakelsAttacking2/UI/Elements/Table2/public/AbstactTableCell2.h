//
// Purpur Tentakel
// 03.04.2023
//

#include "UIElement.hpp"
#include "Focusable.h"

class AbstactTableCell2 : public UIElement, public Focusable {
private:
	bool m_isEditable = true; ///< contains if the cell is currently editable
	float m_textSize; ///< contains the text size the text is renderd with

	/**
	 * calculates a new text size from the collider.
	 */
	void CalculateTextSize(std::string const& value);

public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	AbstactTableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID);

	/**
	 * sets if the cell is editable.
	 */
	void SetIsEditable(bool IsEditable);
	/**
	 * returns true if the cell is editable.
	 */
	[[nodiscard]] bool IsEditable() const;

	/**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the cell.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext const&) override;
	/**
	 * renders the cell.
	 */
	void Render(AppContext const& appContext) override;
};