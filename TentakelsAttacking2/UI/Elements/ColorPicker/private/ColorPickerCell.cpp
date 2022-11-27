//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorPickerCell.h"
#include "ColorPicker.h"
#include "AppContext.h"
#include "HFocusEvents.h"
#include "HInput.h"
#include <iostream>

void ColorPickerCell::SetColor() const {
	m_colorPicker->SetColor(m_color);
}

ColorPickerCell::ColorPickerCell(unsigned int ID, Vector2 pos, Vector2 size, 
	Alignment alignment, Vector2 resolution, Color color, ColorPicker* colorPicker)
	: Focusable(ID), UIElement(pos, size, alignment, resolution),
	m_color(color), m_colorPicker(colorPicker) {

	if (IsBlankCell()) {
		m_enabled = false;
	}
}

Color ColorPickerCell::GetColor() const {
	return m_color;
}

bool ColorPickerCell::IsBlankCell() const {
	return m_color == BLANK;
}
void ColorPickerCell::SetEnabled(bool enabled) {
	if (IsBlankCell()) {
		m_enabled = false;
		return;
	}
	m_enabled = enabled;
}
bool ColorPickerCell::IsEnabled() const {
	return m_enabled;
}
Rectangle ColorPickerCell::GetCollider() const {
	return UIElement::GetCollider();
}

void ColorPickerCell::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	if (!m_enabled) {
		return;
	}

	bool mouseClick =
		CheckCollisionPointRec(mousePosition, m_colider)
		&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	if (mouseClick) {
		m_colorPicker->SetCellFocuses(appContext);

		SelectFocusElement(this, m_colorPicker->IsPopUp());
	}

	bool enterClick =
		IsFocused()
		&& IsConfirmInputPressed();
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

	Color color = m_color != PURPLE ? PURPLE : DARKPURPLE;
	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		color
	);
}
