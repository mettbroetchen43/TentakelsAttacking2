//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"

class ColorPicker;

class ColorPickerCell final : public UIElement, public Focusable {
private:
	bool m_enabled = true;
	Rectangle m_colider;
	Color m_color;
	ColorPicker* m_colorPicker;

	void SetColor() const;

	void UpdateColider(Vector2 resolution) override;

public:
	ColorPickerCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution, Color color, ColorPicker* colorPicker);

	[[nodiscard]] Color GetColor() const;

	[[nodiscard]] bool IsBlankCell() const;
	void SetEnabled(bool enabled);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};