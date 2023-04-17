//
// Purpur Tentakel
// 07.04.2023
//

#include "AbstactTableCell2.h"

void AbstactTableCell2::CalculateTextSize() {
	m_textSize = m_collider.height / 3;
	m_textPosition = { m_collider.x + m_collider.width * 0.05f ,m_collider.y + m_textSize };
}

AbstactTableCell2::AbstactTableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID)
	: UIElement(pos, size, alignment, resolution), Focusable(focusID), m_textSize(0.0f), m_textPosition({ 0.0f,0.0f }) {
	CalculateTextSize();
}

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

void AbstactTableCell2::CheckAndUpdate(Vector2 const&, AppContext const&) {

}
void AbstactTableCell2::Render(AppContext const&) {
	DrawRectangleLinesEx(
		m_collider,
		1.0f,
		WHITE
	);
}
