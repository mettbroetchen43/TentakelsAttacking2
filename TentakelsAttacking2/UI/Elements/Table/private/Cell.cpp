//
// Purpur Tentakel
// 29.09.22
//

#include "Cell.h"
#include "AppContext.h"

bool Cell::ShouldEdit(Vector2 const& mousePosition) const {
	bool edit = false;

	if (!m_editable) {
		return edit;
	}

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
		auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}

	return edit;
}

void Cell::ClampNeededSize(Vector2& neededSize) const {
	neededSize.x = neededSize.x < m_minSize.x ? m_minSize.x : neededSize.x;
	neededSize.x = neededSize.x > m_maxSize.x ? m_maxSize.x : neededSize.x;

	neededSize.y = neededSize.y < m_minSize.y ? m_minSize.y : neededSize.y;
	neededSize.y = neededSize.y > m_maxSize.y ? m_maxSize.y : neededSize.y;
}

Cell::Cell(Vector2 pos, Vector2 size, Alignment alignment,
	unsigned int ID, Vector2 resolution, Table* table)
	: UIElement(pos, size, alignment), Focusable(ID), m_table(table) {

	m_minSize = {
		m_size.x / 2,
		m_size.y / 2
	};
	m_maxSize = {
		m_size.x * 2,
		m_size.y * 2
	};

	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_textSize = m_colider.height / 2;
	m_textPosition = {
		m_colider.x + m_colider.width / 20,
		m_colider.y + m_colider.height / 4
	};
}

void Cell::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	if (!m_editable) {
		return;
	}

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

Table* Cell::GetTable() const {
	return m_table;
}

void Cell::SetEditable(bool editable) {
	m_editable = editable;
}
bool Cell::IsEnabled() const {
	return m_editable;
}
Rectangle Cell::GetCollider() const {
	return m_colider;
}
