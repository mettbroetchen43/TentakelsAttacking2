//
// Purpur Tentakel
// 09.11.2022
//

#include "PlanetUI.h"
#include "AppContext.h"
#include <iostream>

void PlanetUI::UpdateColider(Vector2 resolution) {
	m_colider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.y * resolution.y,
		m_size.y * resolution.y
	};
}

PlanetUI::PlanetUI(Vector2 pos, unsigned int ID, Color color, Vector2 resolution)
	: UIElement(pos, {0.02f,0.02f}, Alignment::MID_MID), m_ID(ID), m_color(color) {
	
	m_colider = GetAlignedCollider(m_pos, m_size, m_alignment, resolution);
}

void PlanetUI::CheckAndUpdate(Vector2 const& mousePosition, AppContext const&) {
	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		std::cout << "HIT | PLANET | ID: " << m_ID << '\n';
	}
}
void PlanetUI::Render(AppContext const& appContext) {
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		std::to_string(m_ID).c_str(),
		Vector2 { m_colider.x, m_colider.y },
		m_colider.height,
		0.0f,
		m_color
	);
}
void PlanetUI::Resize(Vector2 resolution, AppContext const&) {
	UpdateColider(resolution);
}

[[nodiscard]] unsigned int PlanetUI::GetID() const {
	return m_ID;
}
[[nodiscard]] Color PlanetUI::GetColor() const {
	return m_color;
}