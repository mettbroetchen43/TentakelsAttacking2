//
// Purpur Tentakel
// 12.11.2022
//

#include "UIGalaxy.h"

UIGalaxy::UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution)
	:Focusable(ID), UIElement(pos, size, alignment) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_absoluteSize = m_colider; // just for testing. need to chance to actual galaxy size.
}

void UIGalaxy::UpdateColider(Vector2 resolution) {
	m_colider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
	// need to scale m_absoluteSize
}

void UIGalaxy::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {}
void UIGalaxy::Render(AppContext const& appContext) {
	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);
	DrawRectangleLinesEx(
		m_absoluteSize,
		3.0f,
		PURPLE
	);
}
void UIGalaxy::Resize(Vector2 resolution, AppContext const& appContext) {
	m_colider = {
	m_pos.x * resolution.x,
	m_pos.y * resolution.y,
	m_size.x * resolution.x,
	m_size.y * resolution.y
	};
	// need to scale m_absoluteSize
}


void UIGalaxy::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
}
bool UIGalaxy::IsEnabled() const {
	return m_isEnabled;
}
Rectangle UIGalaxy::GetCollider() const {
	return m_colider;
}

void UIGalaxy::OnEvent(Event const& event) {}
