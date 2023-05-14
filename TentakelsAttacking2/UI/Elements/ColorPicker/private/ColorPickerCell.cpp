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
	m_color(color), m_colorPicker(colorPicker),
	m_hover(
		0.05f,
		AppContext::GetInstance().colors.AsString(color),
		WHITE,
		{0.01f,0.01f},
		resolution)
		{

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

bool ColorPickerCell::IsHover() const {
	return m_renderHover;
}

void ColorPickerCell::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);
	m_hover.CheckAndUpdate(mousePosition, appContext);

	if (!m_enabled) {
		return;
	}

	m_renderHover = CheckCollisionPointRec(mousePosition, m_collider);
	if (m_renderHover) {
		m_hover.SetRenderHover(mousePosition, appContext);
	}

	bool mouseClick =
		m_renderHover
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
		m_collider,
		Vector2(0.0f, 0.0f),
		0.0f,
		m_color
	);

	Color color = m_color != PURPLE ? PURPLE : DARKPURPLE;
	DrawRectangleLinesEx(
		m_collider,
		3.0f,
		color
	);
}

void ColorPickerCell::RenderHover(AppContext const& appContext) {
	m_hover.Render(appContext);
}
