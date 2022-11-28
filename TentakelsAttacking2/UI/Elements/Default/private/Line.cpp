//
// Purpur Tentakel
// 06.10.2022
//

#include "Line.h"

Line::Line(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	float thick)
	: UIElement(pos, size, alignment, resolution), m_thick(thick) { }

void Line::Render([[maybe_unused]] AppContext const& appContext) {
	DrawLineEx(
		Vector2(
			m_colider.x,
			m_colider.y
		),
		Vector2(
			m_colider.x + m_colider.width,
			m_colider.y + m_colider.height
		),
		m_thick,
		WHITE
	);
}

