//
// Purpur Tentakel
// 15.08.2022
//

#include "Button.h"
#include "SoundManager.h"

Button::~Button() {
	UnloadTexture(m_texture);
}

void Button::SetTextSizeAndPosition(Vector2 resolution) {
	m_textSize = m_collider.height / 3;
	int textWidth = MeasureText(m_text.c_str(), m_textSize);
	while (textWidth > m_collider.width) {
		if (m_textSize == 1) {
			break;
		}

		m_textSize -= 1;
		textWidth = MeasureText(m_text.c_str(), m_textSize);
	}

	m_textPosition.x = resolution.x * m_pos.x + (resolution.x * m_size.x / 2 - textWidth / 2);
	m_textPosition.y = resolution.y * m_pos.y + (resolution.y * m_size.y / 2 - m_textSize / 2);
}

bool Button::IsSameState(State state) const {
	return m_state == state;
}

Button::Button(std::string const& file, Vector2 pos, Vector2 size, Vector2 resolution, std::string const& text, SoundType releaseSound, std::function<void()> onClick)
	: UIElement(size, pos), m_file(file), m_text(text),m_sound(releaseSound), m_onClick(onClick) {
	m_texture = LoadTexture(file.c_str());
	m_textureRec = { 0,0, static_cast<float>(m_texture.width) ,static_cast<float>(m_texture.height / m_buttonParts)};
	m_collider = { resolution.x * pos.x, resolution.y * pos.y, resolution.x * size.x, resolution.y * size.y };

	SetTextSizeAndPosition(resolution);
}

void Button::CheckAndUpdate(Vector2 const& mousePosition, SoundManager const& soundManager) {
	bool const hover = CheckCollisionPointRec(mousePosition, m_collider);
	if (m_state == State::DISABLED) {
		if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			soundManager.PlaySound(SoundType::CLICKED_DISABLED_STD);
		}
		return;
	}

	if (!hover) {
		if (IsSameState(State::HOVER)) {
			soundManager.PlaySound(SoundType::HOVER_STD);
		}
		m_state = State::ENABLED;
		return;
	}

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		if (!IsSameState(State::PRESSED)) {
			soundManager.PlaySound(SoundType::CLICKED_PRESS_STD);
		}
		m_state = State::PRESSED;
	}
	else {
		if (IsSameState(State::ENABLED)) {
			soundManager.PlaySound(SoundType::HOVER_STD);
		}
		m_state = State::HOVER;
	}

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		soundManager.PlaySound(m_sound);
		m_onClick();
	}
}

void Button::Render() {
	m_textureRec.y = static_cast<int>(m_state) * m_textureRec.height;
	DrawTexturePro(m_texture, m_textureRec, m_collider, Vector2(0.0f, 0.0f), 0, WHITE);
	DrawText(m_text.c_str(), static_cast<int>(m_textPosition.x), static_cast<int>(m_textPosition.y), m_textSize, WHITE);
}

void Button::Resize(Vector2 resolution) {
	m_collider = { resolution.x * m_pos.x, resolution.y * m_pos.y, resolution.x * m_size.x, resolution.y * m_size.y };
	SetTextSizeAndPosition(resolution);
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
