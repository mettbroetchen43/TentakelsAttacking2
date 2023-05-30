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
void LineDrag::SetCallback(std::function<void(Vector2,Vector2)> callback) {
	m_callback = callback;
}
void LineDrag::ClearCallback() {
	m_callback = [](Vector2, Vector2) {};
}
