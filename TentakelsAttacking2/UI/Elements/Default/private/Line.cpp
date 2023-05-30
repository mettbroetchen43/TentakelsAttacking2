//
// Purpur Tentakel
// 06.10.2022
//

#include "Line.h"

Line::Line(Vector2 start, Vector2 end, Vector2 resolution, float thick, Color color)
	: UIElement{ start, end - start, Alignment::DEFAULT, resolution }, m_thick{ thick }, m_color{ color } { }

void Line::Render(AppContext const&) {
	DrawLineEx(
		Vector2(
			m_collider.x,
			m_collider.y
		),
		Vector2(
			m_collider.x + m_collider.width,
			m_collider.y + m_collider.height
		),
		m_thick,
		m_color
	);
}

