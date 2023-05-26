//
// Purpur Tentakel
// 25.05.2023
//

#pragma once
#include "UIElement.hpp"
#include <memory>

class Line;



class Arrow final : public UIElement {
private:
	Line_ty m_long; ///< contains the long line of the arrow
	Line_ty m_shortLeft; ///< contains the line that goes to the left when the arrow points upwards
	Line_ty m_shortRight; ///< contains the line that goes to the right when the arrow points upwards
	Alignment m_direction; ///< contains the direction the arrow is pointing to
	Color m_color; ///< contains the color the arrow is rendered with
	float m_thick; ///< contains how thick the lines of the arrow are

	/**
	 * validates if the direction is valid.
	 */
	void ValidateDirection();

	/**
	 * calculates the position an size of the lines.
	 */
	void CalculateLines();
	/**
	 * Calculates the long line.
	 */
	void CalculatesLongLine();
	/**
	 * calculates the two short lines.
	 */
	void CalculatesShortLines();

public:
	Arrow(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Alignment direction, Color color, float thick);

	/**
	 * sets the direction the arrow is pointing to.
	 * notice that Alignment::MID_MID is invalid.
	 */
	void SetDirection(Alignment direction);
	/**
	 * returns the direction the arrow is pointing to.
	 */
	[[nodiscard]] Alignment GetDirection() const;

	/**
	 * calls the lines to render.
	 */
	void Render(AppContext_ty_c appContext);
};