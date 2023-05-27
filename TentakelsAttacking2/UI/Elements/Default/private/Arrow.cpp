//
// Purpur Tentakel
// 25.05.2023
//

#include "Arrow.h"
#include "Line.h"
#include "HGeneral.h"
#include <cassert>
#include <stdexcept>
#include <numbers>
#include "HPrint.h"


void Arrow::CalculateLines() {
	CalculatesLongLine();
	CalculatesShortLines();
}

void Arrow::CalculatesLongLine() {
	m_long = std::make_shared<Line>(
		m_start,
		GetLongLineLength(),
		Alignment::DEFAULT,
		m_resolution,
		m_thick,
		m_color
	);
}
void Arrow::CalculatesShortLines() {

}

Vector2 Arrow::GetLeftSchortEnd() {
	Vector2 end{ GetGlobalShortEnd() };
	float len{ LenVec2(m_end - end) };
	float angle{ 45 * std::numbers::pi / 180 };
	end.x = end.x + cos(angle) * len;
	end.y = end.y + sin(angle) * len;
	return end;
}

Vector2 Arrow::GetGlobalShortEnd() {
	Vector2 line{ GetLongLineLength() };
	line = line / m_scale;
	return{ m_end - line };
}

Vector2 Arrow::GetLongLineLength() {
	return 	{ m_end - m_start };
}

Arrow::Arrow(Vector2 start, Vector2 end, Alignment alignment, Vector2 resolution, Color color, float thick)
	: UIElement{ start, {end - start}, alignment, resolution }, m_start{ start }, m_end{ end },
	m_color{ color }, m_thick{ thick } {
	CalculateLines();
}

void Arrow::Update() {
	SetSize(GetLongLineLength());
	m_long->SetPosition(m_start);
	m_long->SetSize(GetLongLineLength());
}



void Arrow::SetEnd(Vector2 end) noexcept {
	m_end = end;
}

void Arrow::SetScale(float scale) noexcept {
	m_scale = scale;
}

void Arrow::Render(AppContext_ty_c appContext) {
	m_long->Render(appContext);
	Vector2 end{ GetLeftSchortEnd() };
	Print(std::to_string(end.x * m_resolution.x) + " | " + std::to_string(end.y * m_resolution.y), PrintType::DEBUG);
	DrawLineEx(
		{ m_end.x * m_resolution.x,
		m_end.y * m_resolution.y },
		{ end.x * m_resolution.x,
		end.y * m_resolution.y },
		5.0f,
		WHITE
	);
	// m_shortLeft->Render(appContext);
	// m_shortRight->Render(appContext);
}
