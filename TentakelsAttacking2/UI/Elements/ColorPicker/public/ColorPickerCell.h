//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"

class ColorPicker;

/**
 * provides the coll for the colorpicker.
 */
class ColorPickerCell final : public UIElement, public Focusable {
private:
	bool m_enabled = true; ///< contains if the cell is enabled
	Color m_color; ///< contains the color of the cell
	ColorPicker* m_colorPicker; ///< contans a pointer to the colorpicker it belongs to

	/**
	 * calls the colorpicker to set the cell color as current color.
	 */
	void SetColor() const;

public:
	/**
	 * ctor.
	 * only initialize.
	 */
	ColorPickerCell(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution, Color color, ColorPicker* colorPicker);

	/**
	 * returns the current color.
	 */
	[[nodiscard]] Color GetColor() const;

	/**
	 * returns if the cell contains a current color.
	 */
	[[nodiscard]] bool IsBlankCell() const;
	/**
	 * sets if the current cell is enabled.
	 */
	void SetEnabled(bool enabled);
	/**
	 * returns if the current cell is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns thet current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * logic of the cell.
	 * triggers the color picker to update specific memebr functions
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the cell.
	 */
	void Render(AppContext const& appContext) override;
};