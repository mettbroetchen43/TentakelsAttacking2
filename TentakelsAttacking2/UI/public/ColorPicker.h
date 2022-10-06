//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "ColorPickerCell.h"
#include <array>
#include <memory>


class ColorPicker : public UIElement, public Focusable {
private:
	bool m_focusedCells = false;
	size_t m_countX = 4;
	size_t m_countY = 4;
	Texture* m_backGround;
	Rectangle m_colider;
	std::array<Color, 16> m_colors = {
		YELLOW,
		GOLD,
		PINK,
		MAGENTA,
		ORANGE,
		RED,
		MAROON,
		GREEN,
		LIME,
		DARKGREEN,
		SKYBLUE,
		BLUE,
		DARKBLUE,
		PURPLE,
		VIOLET,
		DARKPURPLE,
	};
	std::array<std::unique_ptr<ColorPickerCell>, 16> m_cells;
	ColorPickerCell* m_currentColorCell = nullptr;

	void Initialise(Vector2 resolution);

public:
	ColorPicker(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution);
	~ColorPicker() override;

	[[nodiscard]] Color GetColor();
	bool SetColor(Color color);

	void SetCellFocuses(AppContext const& appContext);
	void SetEnabled(bool enabled, Color color);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
