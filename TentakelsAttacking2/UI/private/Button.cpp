//
// Purpur Tentakel
// 15.08.2022
//

#include "Button.h"

Button::~Button() {
	UnloadTexture(m_texture);
}
Button::Button(std::string const& file, float posX, float posY, std::string const& text, std::function<void()> onClick)
	: m_file(file), m_text(text), m_onClick(onClick) {
	m_texture = LoadTexture(file.c_str());
	float frameHight = static_cast<float>(m_texture.height) / m_buttonParts;
	m_textureRec = { 0,0,static_cast<float>(m_texture.width),frameHight };
	m_colider = { posX, posY, static_cast<float>(m_texture.width), frameHight };

	int textWith = MeasureText(m_text.c_str(), m_textSize);
	m_textPosition.x = posX + (m_texture.width / 2 - textWith / 2);
	m_textPosition.y = posY +(m_texture.height / m_buttonParts / 2 - m_textSize / 2);
}

void Button::CheckAndUpdate(Vector2 const& mousePosition) {
	if (m_state == State::DISABLED) {
		return;
	}

	if (!CheckCollisionPointRec(mousePosition, m_colider)) {
		m_state = State::ENABLED;
		return;
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		m_state = State::PRESSED;
	}
	else {
		m_state = State::HOVER;
	}

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		m_onClick();
	}
}

void Button::Render() {
	m_textureRec.y = static_cast<int>(m_state) * m_textureRec.height;
	DrawTextureRec(m_texture, m_textureRec, Vector2(m_colider.x, m_colider.y),WHITE);
	DrawText(m_text.c_str(), static_cast<int>(m_textPosition.x), static_cast<int>(m_textPosition.y), m_textSize, WHITE);
}

void Button::SetEnabled(bool enabled) {
	if (enabled) {
		m_state = State::ENABLED;
	}
	else {
		m_state = State::DISABLED;
	}
}

bool Button::IsEnabled() const {
	return m_state == State::ENABLED;
}
