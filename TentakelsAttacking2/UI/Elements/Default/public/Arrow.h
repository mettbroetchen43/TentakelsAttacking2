//
// Purpur Tentakel
// 25.05.2023
//

#pragma once
#include "UIElement.hpp"
#include <memory>

class Arrow final : public UIElement {
private:
	float m_scale{ 5.0f }; ///< contains the scale between short and long lines

	Vector2 m_start; ///< contains the absolute start position 
	Vector2 m_end; ///< contains the absolute end position
	Line_ty m_long; ///< contains the long line of the arrow
	Line_ty m_shortLeft; ///< contains the line that goes to the left when the arrow points upwards
	Line_ty m_shortRight; ///< contains the line that goes to the right when the arrow points upwards
	Color m_color; ///< contains the color the arrow is rendered with
	float m_thick; ///< contains how thick the lines of the arrow are

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
	/**
	 * returns the end point of the left short line.
	 */
	Vector2 GetLeftSchortEnd();
	/**
	 * return the end point of the right short line.
	 */
	Vector2 GetRightShortEnd();
	/**
	 * calculates the endpoint of the short lines onto the long line.
	 */
	Vector2 GetGlobalShortEnd();
	/**
	 * returns the length of the long line.
	 */
	Vector2 GetLongLineLength();


public:
	Arrow(Vector2 start, Vector2 end, Alignment alignment, Vector2 resolution, Color color, float thick);

	/**
	 * updates the previous changes.
	 */
	void Update();

	/** 
	 * sets a new end value.
	 * need of update.
	 */
	void SetEnd(Vector2 end) noexcept;
	/**
	 * sets a new scale.
	 * the scale describes how many time the long line could contain the short lines.
	 * need of update
	 */
	void SetScale(float scale) noexcept;

	/**
	 * calls the lines to render.
	 */
	void Render(AppContext_ty_c appContext);
};