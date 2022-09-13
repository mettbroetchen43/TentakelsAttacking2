//
// Purpur Tentakel
// 15.08.2022
//

#include "Button.h"
#include "AppContext.h"

void Button::SetTextSizeAndPosition(Vector2 resolution, AppContext const& appContext) {
	m_textSize = m_collider.height / 2;
	Vector2 textSize= MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		m_text.c_str(),
		m_textSize,
		0.0f);
	while (textSize.x > m_collider.width) {
		if (m_textSize == 1) {
			break;
		}

		m_textSize -= 1;
		textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			m_text.c_str(),
			m_textSize,
			0.0f);
	}

	m_textPosition.x = resolution.x * m_pos.x + (resolution.x * m_size.x / 2 - textSize.x / 2);
	m_textPosition.y = resolution.y * m_pos.y + (resolution.y * m_size.y / 2 - m_textSize / 2);
}

bool Button::IsSameState(State state) const {
	return m_state == state;
}

Button::Button(Texture2D* texture, Vector2 pos, Vector2 size, Vector2 resolution,
	std::string const& text, SoundType releaseSound)
	: UIElement(pos, size), m_texture(texture), m_text(text), m_sound(releaseSound) {
	m_textureRec = { 0,0, static_cast<float>(m_texture->width) ,static_cast<float>(m_texture->height / m_buttonParts)};
	m_collider = { resolution.x * pos.x, resolution.y * pos.y, resolution.x * size.x, resolution.y * size.y };

	SetTextSizeAndPosition(resolution, AppContext::GetInstance());
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
			m_state = hover? State::HOVER : State::ENABLED;
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
void Button::Render(AppContext const& appContext) {
	m_textureRec.y = static_cast<int>(m_state) * m_textureRec.height;
	DrawTexturePro(*m_texture, m_textureRec, m_collider, Vector2(0.0f, 0.0f), 0, WHITE);
	DrawTextEx(
		*(appContext.assetManager.GetFont()), m_text.c_str(),
		Vector2(m_textPosition.x, m_textPosition.y),
		static_cast<float>(m_textSize),
		0,
		WHITE);
}
void Button::Resize(Vector2 resolution, AppContext const& appContext) {
	m_collider = { resolution.x * m_pos.x, resolution.y * m_pos.y, resolution.x * m_size.x, resolution.y * m_size.y };
	SetTextSizeAndPosition(resolution, appContext);
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
	m_textPosition.x += (collider.x - m_collider.x);
	m_textPosition.y += (collider.y - m_collider.y);
	m_collider = collider;
}
