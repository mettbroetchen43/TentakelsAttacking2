//
// Purpur Tentakel
// 04.09.2022
//

#include "ClassicButton.h"
#include "AppContext.h"

ClassicButton::ClassicButton(unsigned int focusID, Vector2 pos, Vector2 size, Alignment allignment,
	Vector2 resolution, std::string const& text, Texture2D* texture, SoundType releaseSound)
	: Focusable(focusID), Button(pos, size, allignment, text, texture, releaseSound, resolution) { }

void ClassicButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

	if (IsFocused()) {
		if (m_state == State::DISABLED) {
			if (IsKeyPressed(KEY_ENTER) or IsKeyPressed(KEY_SPACE)) {
				auto event = PlaySoundEvent(SoundType::CLICKED_DISABLED_STD);
				appContext.eventManager.InvokeEvent(event);
				return;
			}

			bool disabledAction =
				IsKeyDown(KEY_ENTER) or
				IsKeyDown(KEY_SPACE) or
				IsKeyReleased(KEY_ENTER) or
				IsKeyReleased(KEY_SPACE);
			if (disabledAction) {
				return;
			}
		}

		if (IsKeyPressed(KEY_ENTER) or IsKeyPressed(KEY_SPACE)) {
			if (m_state != State::PRESSED) {
				m_state = State::PRESSED;
				m_isPressed = true;
				auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
				appContext.eventManager.InvokeEvent(event);
				return;
			}
		}

		if (IsKeyDown(KEY_ENTER) or IsKeyDown(KEY_SPACE)) {
			m_state = State::PRESSED;
			m_onPress();
			return;
		}

		if (IsKeyReleased(KEY_ENTER) or IsKeyReleased(KEY_SPACE)) {
			bool hover = CheckCollisionPointRec(mousePosition, m_collider);
			if (!hover or !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				m_state = hover ? State::HOVER : State::ENABLED;
				m_isPressed = false;

				auto event = PlaySoundEvent(m_sound);
				appContext.eventManager.InvokeEvent(event);
				m_onClick();
				return;
			}
		}
	}

	Button::CheckAndUpdate(mousePosition, appContext);
}

Rectangle ClassicButton::GetCollider() const {
	return m_collider;
}
