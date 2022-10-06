//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorPickerCell.h"
#include "ColorPicker.h"
#include "AppContext.h"

void ColorPickerCell::SetColor() const {
	m_colorPicker->SetColor(m_color);
}

ColorPickerCell::ColorPickerCell(unsigned int ID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution, Color color, ColorPicker* colorPicker)
	: Focusable(ID), UIElement(pos, size, alignment),
	m_color(color), m_colorPicker(colorPicker) {

	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
}

Color ColorPickerCell::GetColor() const {
	return m_color;
}

void ColorPickerCell::SetEnabled(bool enabled) {
	m_enabled = enabled;
}
bool ColorPickerCell::IsEnabled() const {
	return m_enabled;
}
Rectangle ColorPickerCell::GetCollider() const {
	return m_colider;
}

void ColorPickerCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	bool mouseClick =
		CheckCollisionPointRec(mousePosition, m_colider)
		&& IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	if (mouseClick) {
		m_colorPicker->SetCellFocuses(appContext);

		auto event = SelectFocusElementEvent(this);
		appContext.eventManager.InvokeEvent(event);
	}

	bool enterClick =
		IsFocused()
		&& IsKeyPressed(KEY_ENTER);
	if (mouseClick or enterClick) {
		m_colorPicker->SetColor(m_color);
	}
}
void ColorPickerCell::Render([[maybe_unused]] AppContext const& appContext) {
	if (!m_enabled) {
		return;
	}

	DrawRectanglePro(
		m_colider,
		Vector2(0.0f, 0.0f),
		0.0f,
		m_color
	);

	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		PURPLE
	);
}
void ColorPickerCell::Resize(Vector2 resolution,
	[[maybe_unused]] AppContext const& appContext) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
}