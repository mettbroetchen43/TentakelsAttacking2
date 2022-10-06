//
// Purpur Tentakel
// 29.09.22
//

#include "Cell.h"
#include "AppContext.h"

bool Cell::ShouldEdit(Vector2 const& mousePosition) const {
	bool edit = false;

	if (IsFocused()) {
		if (IsKeyPressed(KEY_ENTER)
			or IsKeyPressed(KEY_SPACE)) {
			edit = true;
		}
	}
	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			edit = true;
		}
	}

	if (edit) {
		AppContext::GetInstance().soundManager.PlaySound(SoundType::CLICKED_PRESS_STD);
	}

	return edit;
}

Cell::Cell(Vector2 pos, Vector2 size, Alignment alignment,
	unsigned int ID, Vector2 resolution)
	: UIElement(pos, size, alignment), Focusable(ID) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_textSize = m_colider.height / 2;
	m_textPosition = {
		m_colider.x + m_colider.width / 20,
		m_colider.y + m_colider.height / 4
	};
}

void Cell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			auto event = SelectFocusElementEvent(this);
			appContext.eventManager.InvokeEvent(event);
		}
	}
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
	m_textSize = m_colider.height / 2;
	m_textPosition = {
	m_colider.x + m_colider.width / 20,
	m_colider.y + m_colider.height / 4
	};
}

bool Cell::IsEnabled() const {
	return true;
}
Rectangle Cell::GetCollider() const {
	return m_colider;
}
