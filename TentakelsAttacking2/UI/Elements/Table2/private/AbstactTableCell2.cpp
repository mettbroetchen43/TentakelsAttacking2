//
// Purpur Tentakel
// 07.04.2023
//

#include "AbstactTableCell2.h"

AbstactTableCell2::AbstactTableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID)
	: UIElement(pos, size, alignment, resolution), Focusable(focusID) { }

void AbstactTableCell2::SetEditable(bool IsEditable) noexcept {
	m_isEditable = IsEditable;
}
bool AbstactTableCell2::IsEditable() const noexcept {
	return m_isEditable;
}

bool AbstactTableCell2::IsEnabled() const noexcept {
	return true;
}
Rectangle AbstactTableCell2::GetCollider() const noexcept{
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
