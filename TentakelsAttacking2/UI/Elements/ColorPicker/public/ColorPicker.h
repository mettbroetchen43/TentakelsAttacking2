//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "ColorPickerCell.h"
#include <vector>
#include <functional>
#include <memory>


class ColorPicker final : public UIElement, public Focusable {
private:
	bool m_isPopUp;

	size_t m_countX;
	size_t m_countY;
	Texture* m_backGround;
	std::vector<std::unique_ptr<ColorPickerCell>> m_cells;
	ColorPickerCell* m_currentColorCell = nullptr;
	ColorPickerCell* m_previousColorCell = nullptr;
	std::function<void()> m_onEnter = []() {};

	void Initialise(Vector2 resolution);
	void SetUsedColors(AppContext const& appContext);
	void SetColorFromFocus();
	void CheckforValidColor(AppContext const& appContext);

public:
	ColorPicker(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution, bool isPopUp = false);
	~ColorPicker() override;

	[[nodiscard]] Color GetColor() const;
	[[nodiscard]] bool HasColorChanced() const;
	bool SetInitialColor(Color color);
	bool SetColor(Color color);

	void SetOnEnter(std::function<void()> onEnter);

	void SetCellFocuses(AppContext const& appContext);
	void SetEnabled(bool enabled, Color color);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] bool IsPopUp() const;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
