//
// Purpur Tentakel
// 15.08.2022
//

#include "Button.h"

Button::~Button() {
	UnloadTexture(m_texture);
}

Button::Button(std::string const& file, float posX, float posY, std::function<void()> onClick)
	: m_onClick(onClick) {
	m_texture = LoadTexture(file.c_str());
	float frameHight = static_cast<float>(m_texture.height) / m_buttonParts;
	m_textureRec = { 0,0,static_cast<float>(m_texture.width),frameHight };
	m_colider = { posX, posY, static_cast<float>(m_texture.width), frameHight };
}

void Button::CheckAndUpdate(Vector2 const& mousePosition) {
	bool isChecked = false;
	if (!CheckCollisionPointRec(mousePosition, m_colider)) {
		m_state = State::CLEAR;
		return;
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		m_state = State::PRESSED;
	}
	else {
		m_state = State::HOVER;
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		m_onClick();
	}
}

void Button::Render() {
	m_textureRec.y = static_cast<int>(m_state) * m_textureRec.height;
	DrawTextureRec(m_texture, m_textureRec, Vector2(m_colider.x, m_colider.y),WHITE);
}
