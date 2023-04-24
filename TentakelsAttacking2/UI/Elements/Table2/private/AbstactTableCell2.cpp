//
// Purpur Tentakel
// 07.04.2023
//

#include "HPrint.h"
#include "AbstactTableCell2.h"


AbstactTableCell2::AbstactTableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID)
	: UIElement(pos, size, alignment, resolution), Focusable(focusID), m_textSize(0.0f), m_textPosition({ 0.0f,0.0f }){ }

void AbstactTableCell2::SetEditable(bool IsEditable) noexcept {
	m_isEditable = IsEditable;
}
bool AbstactTableCell2::IsEditable() const noexcept {
	return m_isEditable;
}
bool AbstactTableCell2::IsEnabled() const noexcept {
	return m_isEditable;
}

Rectangle AbstactTableCell2::GetCollider() const noexcept {
	return m_collider;
}
bool AbstactTableCell2::IsColliding(Vector2 point) const {
	return CheckCollisionPointRec(point, m_collider);
}

void AbstactTableCell2::Render(AppContext const&) {

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
