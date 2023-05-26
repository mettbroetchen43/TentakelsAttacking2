//
// Purpur Tentakel
// 25.05.2023
//

#include "Arrow.h"
#include "Line.h"
#include "HGeneral.h"
#include <cassert>
#include <stdexcept>

void Arrow::ValidateDirection() {
	assert(m_direction != Alignment::MID_MID);
	if (m_direction == Alignment::TOP_MID) { m_direction = Alignment::TOP_MID; };
}

void Arrow::CalculateLines() {
	CalculatesLongLine();
	// CalculatesShortLines();
}

void Arrow::CalculatesLongLine() {
	Vector2 size{ m_size }, pos{ m_pos };
	switch (m_direction) {
		default:
		case Alignment::DEFAULT:
		case Alignment::TOP_LEFT:
			// no alignment needed
			break;
		case Alignment::TOP_MID:
			pos.x += size.x / 2;
			size.x = 0.0f;
			break;
		case Alignment::TOP_RIGHT:
			pos.x += size.x;
			size.x *= -1;
			break;
		case Alignment::MID_LEFT:
			pos.y += size.y / 2;
			size.y = 0.0f;
			break;
		case Alignment::MID_MID:
			throw std::invalid_argument("Mid Mid is not valid for an Arrow");
			break;
		case Alignment::MID_RIGHT:
			pos.y += size.y / 2;
			pos.x += size.x;
			size.y = 0.0f;
			size.x *= -1;
			break;
		case Alignment::BOTTOM_LEFT:
			pos.y += size.y;
			size.y *= -1;
			break;
		case Alignment::BOTTOM_MID:
			pos.y += size.y;
			pos.x += size.x / 2;
			size.y *= -1;
			size.x = 0.0f;
			break;
		case Alignment::BOTTOM_RIGHT:
			pos.y += size.y;
			pos.x += size.x;
			size.y *= -1;
			size.x *= -1;
			break;
	}

	m_long = std::make_shared<Line>(
		pos,
		size,
		Alignment::TOP_LEFT,
		m_resolution,
		m_thick,
		m_color
	);
}

Arrow::Arrow(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Alignment direction, Color color, float thick)
	: UIElement{ pos, size, alignment, resolution }, m_direction{ direction }, m_color{ color }, m_thick{ thick } {
	ValidateDirection();
	CalculateLines();
}

void Arrow::SetDirection(Alignment direction) {
	m_direction = direction;
	ValidateDirection();
	CalculateLines();
}

Alignment Arrow::GetDirection() const {
	return m_direction;
}

void Arrow::Render(AppContext_ty_c appContext){
	m_long->Render(appContext);
	// m_shortLeft->Render(appContext);
	// m_shortRight->Render(appContext);
}
