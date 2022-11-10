//
// Purpur Tentakel
// 06.10.2022
//

#include "Line.h"

void Line::UpdateColider(Vector2 resolution) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
}

Line::Line(Vector2 pos, Vector2 size, Alignment alignment,
	float thick, Vector2 resolution)
	: UIElement(pos, size, alignment), m_thick(thick) {

	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
}

void Line::CheckAndUpdate([[maybe_unused]] Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) { }
void Line::Render([[maybe_unused]] AppContext const& appContext) {
	DrawLineEx(
		Vector2{
			m_colider.x,
			m_colider.y
		},
		Vector2{
			m_colider.x + m_colider.width,
			m_colider.y + m_colider.height
		},
		m_thick,
		WHITE
	);
}
void Line::Resize(Vector2 resolution, 
	[[maybe_unused]] AppContext const& appContext) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
}

