//
// Purpur Tentakel
// 15.08.2022
//

#include "Button.h"
#include "AppContext.h"

void Button::SetTextSizeAndPosition(Vector2 resolution) {
	m_textSize = static_cast<int>(m_collider.height / 3);
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

Button::Button(Texture2D* texture, Vector2 pos, Vector2 size, Vector2 resolution, std::string const& text,
	SoundType releaseSound)
	: UIElement(size, pos), m_texture(texture),m_text(text), m_sound(releaseSound) {
	m_textureRec = { 0,0, static_cast<float>(m_texture->width) ,static_cast<float>(m_texture->height / m_buttonParts)};
	m_collider = { resolution.x * pos.x, resolution.y * pos.y, resolution.x * size.x, resolution.y * size.y };

	SetTextSizeAndPosition(resolution);
}

void Button::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	bool const hover = CheckCollisionPointRec(mousePosition, m_collider);
	if (m_state == State::DISABLED) {
		if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			auto event = PlaySoundEvent(SoundType::CLICKED_DISABLED_STD);
			appContext.eventManager.InvokeEvent(event);
		}
		return;
	}

	if (!hover) {
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			m_isPressed = false;
		}

		if (m_isPressed) {
			m_state = State::ENABLED;
			return;
		}

		if (IsSameState(State::HOVER)) {
			auto event = PlaySoundEvent(SoundType::HOVER_STD);
			appContext.eventManager.InvokeEvent(event);
		}
		m_state = State::ENABLED;
		return;
	}
	
	if (m_isPressed) {
		m_onPress();
		if (!IsSameState(State::PRESSED)) {
			m_state = State::PRESSED;
			return;
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			auto event = PlaySoundEvent(m_sound);
			appContext.eventManager.InvokeEvent(event);
			m_onClick();
			m_state = State::ENABLED;
			m_isPressed = false;
			return;
		}
	}
	else {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			m_isPressed = true;
			m_state = State::PRESSED;
			auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
			appContext.eventManager.InvokeEvent(event);
			m_onPress();
			return;
		}
		if (!IsSameState(State::HOVER)) {
			m_state = State::HOVER;
			auto event = PlaySoundEvent(SoundType::HOVER_STD);
			appContext.eventManager.InvokeEvent(event);
			return;
		}
	}

}
void Button::Render() {
	m_textureRec.y = static_cast<int>(m_state) * m_textureRec.height;
	DrawTexturePro(*m_texture, m_textureRec, m_collider, Vector2(0.0f, 0.0f), 0, WHITE);
	DrawText(m_text.c_str(), static_cast<int>(m_textPosition.x), static_cast<int>(m_textPosition.y), m_textSize, WHITE);
}
void Button::Resize(Vector2 resolution) {
	m_collider = { resolution.x * m_pos.x, resolution.y * m_pos.y, resolution.x * m_size.x, resolution.y * m_size.y };
	SetTextSizeAndPosition(resolution);
}

void Button::SetOnClick(std::function<void()> onClick) {
	m_onClick = onClick;
}
void Button::SetOnPress(std::function<void()> onPress) {
	m_onPress = onPress;
}

void Button::SetEnabled(bool enabled) {
	if (enabled) {
		m_state = State::ENABLED;
	}
	else {
		m_state = State::DISABLED;
		m_isPressed = false;
	}
}
bool Button::IsEnabled() const {
	return m_state == State::ENABLED;
}

Rectangle Button::GetCollider() const {
	return m_collider;
}
void Button::SetCollider(Rectangle collider) {
	m_collider = collider;
}
