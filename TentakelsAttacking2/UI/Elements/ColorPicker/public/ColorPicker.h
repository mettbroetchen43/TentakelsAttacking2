//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "ColorPickerCell.h"
#include <vector>
#include <functional>
#include <memory>

/**
 * provides a Grid of colors to choose from.
 */
class ColorPicker final : public UIElement, public Focusable {
private:
	bool m_isPopUp; ///< contains if the colorpicker was generated inside a popup

	size_t m_countX; ///< contains the count of columns
	size_t m_countY; ///< contains the count of rows
	Texture* m_backGround; ///< contains the texture behind the colors
	std::vector<std::unique_ptr<ColorPickerCell>> m_cells; ///< contains all current color cells
	ColorPickerCell* m_currentColorCell = nullptr; ///< contains the current color cell
	ColorPickerCell* m_previousColorCell = nullptr; ///< contains the previous color cell
	std::function<void()> m_onEnter = []() {}; ///< contains the lambda that is called if confirm input is pressed

	/**
	 * initialases the cells. 
	 */
	void Initialize(Vector2 resolution);
	/**
	 * disables the cells if the colors are already used.
	 */
	void SetUsedColors(AppContext const& appContext);
	/**
	 * retund if not nested focus.
	 * sets the color that is in focus.
	 */
	void SetColorFromFocus();
	/**
	 * chekcks if the current color is valid.
	 * returns if its valid.
	 * calls a valid color via event.
	 */
	void CheckForValidColor(AppContext const& appContext);

public:
	/**
	 * ctor.
	 * only initialisation.
 	 */
	ColorPicker(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution, bool isPopUp = false);
	/**
	 * delets a focus layer if nested focus.
	 */
	~ColorPicker() override;

	/**
	 * returns the current color.
	 * if no current color it returns blank.
	 */
	[[nodiscard]] Color GetColor() const;
	/**
	 * returns if the current culor has chanced since the last tick.
	 */
	[[nodiscard]] bool HasColorChanced() const;
	/**
	 * sets the first color.
	 * calls SetColor.
	 * return if the color was set.
	 */
	bool SetInitialColor(Color color);
	/**
	 * set a specific color if it exists in the color picker.
	 * returns if the color was set.
	 */
	bool SetColor(Color color);

	/**
	 * sets the onEnter lambda that get called if enter is pressed.
	 */
	void SetOnEnter(std::function<void()> onEnter);

	/**
	 * early return if alreaty nested focus.
	 * add a focus layer.
	 * adds all cells as focus element.
	 */
	void SetCellFocuses(AppContext const& appContext);
	/**
	 * sets if a specific color is enabled.
	 */
	void SetEnabled(bool enabled, Color color);
	/**
	 * returns true.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns id the colorpicker was generated inside of an popup.
	 */
	[[nodiscard]] bool IsPopUp() const;

	/**
	 * logic of the colorpicker.
	 * calls all cells to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the colorpicker.
	 * calls all cells to render.
	 */
	void Render(AppContext const& appContext) override;
	/**
	 * resizes the colorpicker.
	 * calls all cells to resize.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	/**
	 * returns the current colider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;
};
