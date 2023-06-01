//
// Purpur Tentakel
// 30.05.2023
//

#include "LineDrag.h"

Vector2 LineDrag::GetStart() const {
	return m_start;
}
Vector2 LineDrag::GetEnd() const {
	return m_end;
}
void LineDrag::SetThick(float thick) {
	m_thick = thick;
}
float LineDrag::GetThick() const {
	return m_thick;
}
void LineDrag::SetColor(Color color) {
	m_color = color;
}
Color LineDrag::GetColor() const {
	return m_color;
}
void LineDrag::SetCallback(std::function<void(Vector2, Vector2)> callback) {
	m_callback = callback;
}
void LineDrag::ClearCallback() {
	m_callback = [](Vector2, Vector2) {};
}

void LineDrag::CheckAndUpdate(Vector2 const& mousePosition, AppContext const&) {
	if (m_render) {
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			m_render = false;
			m_callback(m_start, m_end);
		}
		else {
			m_end = {
				mousePosition.x / m_resolution.x,
				mousePosition.y / m_resolution.y
			};
			SetSize(m_end - m_start);
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			m_render = true;
			m_start = {
				mousePosition.x / m_resolution.x,
				mousePosition.y / m_resolution.y
			};
			m_end = m_start;
			SetPosition(m_start);
			SetSize(m_end - m_start);
		}
	}
}
void LineDrag::Render(AppContext const&) {
	if (m_render) {
		DrawLineEx(
			Vector2{
				m_collider.x,
				m_collider.y
			},
			Vector2{
				m_collider.x + m_collider.width,
				m_collider.y + m_collider.height
			},
			m_thick,
			m_color
		);
	}
}
