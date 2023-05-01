//
// Purpur Tentakel
// 07.04.2023
//

#include "HPrint.h"
#include "AbstractTableCell2.h"


AbstractTableCell2::AbstractTableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID)
	: UIElement(pos, size, alignment, resolution), Focusable(focusID), m_textSize(0.0f), m_textPosition({ 0.0f,0.0f }){ }

void AbstractTableCell2::SetEditable(bool IsEditable) noexcept {
	m_isEditable = IsEditable;
}
bool AbstractTableCell2::IsEditable() const noexcept {
	return m_isEditable;
}
bool AbstractTableCell2::IsEnabled() const noexcept {
	return m_isEditable;
}

Rectangle AbstractTableCell2::GetCollider() const noexcept {
	return m_collider;
}
bool AbstractTableCell2::IsColliding(Vector2 point) const {
	return CheckCollisionPointRec(point, m_collider);
}

void AbstractTableCell2::Render(AppContext const&) {

	DrawRectangleRec(
		m_collider,
		BLACK
	);

	DrawRectangleLinesEx(
		m_collider,
		1.0f,
		WHITE
	);
}
