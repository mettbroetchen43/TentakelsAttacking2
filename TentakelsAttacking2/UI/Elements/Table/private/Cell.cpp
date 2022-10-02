//
// Purpur Tentakel
// 29.09.22
//

#include "Cell.h"

bool Cell::ShouldEdit(Vector2 const& mousePosition) const {
	if (IsFocused()) {
		if (IsKeyPressed(KEY_ENTER)
			or IsKeyPressed(KEY_SPACE)) {
			return true;
		}
	}
	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return true;
		}
	}
	return false;
}

Cell::Cell(Vector2 pos, Vector2 size, Alignment alignment,
	unsigned int ID, Vector2 resolution)
	: UIElement(pos, size, alignment), Focusable(ID) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_textSize = m_colider.height / 3;
	m_textPosition = {
		m_colider.x + m_colider.height / 3,
		m_colider.y + m_colider.width / 20
	};
}

void Cell::Render([[maybe_unused]] AppContext const& appContext) {
	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);
}
void Cell::Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
	m_textSize = m_colider.height / 3;
	m_textPosition = {
	m_colider.x + m_colider.height / 3,
	m_colider.y + m_colider.width / 20
	};
}

bool Cell::IsEnabled() const {
	return true;
}
Rectangle Cell::GetCollider() const {
	return m_colider;
}