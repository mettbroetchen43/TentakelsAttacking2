//
// Purpur Tentakel
// 04.09.2022
//

#include "ClassicButton.h"
#include "AppContext.h"

ClassicButton::ClassicButton(unsigned int focusID, Texture2D* texture, Vector2 pos, Vector2 size,
	Vector2 resolution, std::string const& text, SoundType releaseSound)
	: Button(texture, pos, size, resolution, text, releaseSound), Focusable(focusID) { }

void ClassicButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

	if (IsFocused()) {
		if (m_state == State::DISABLED) {
			if (IsKeyPressed(KEY_ENTER)) {
				auto event = PlaySoundEvent(SoundType::CLICKED_DISABLED_STD);
				appContext.eventManager.InvokeEvent(event);
			}
			return;
		}

		if (IsKeyPressed(KEY_ENTER)) {
			m_state = State::PRESSED;
			auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
			appContext.eventManager.InvokeEvent(event);
			return;
		}

		if (IsKeyDown(KEY_ENTER)) {
			m_state = State::PRESSED;
			m_onPress();
			return;
		}

		if (IsKeyReleased(KEY_ENTER)) {
			bool hover = CheckCollisionPointRec(mousePosition, m_collider);
			m_state = hover ? State::HOVER : State::ENABLED;

			auto event = PlaySoundEvent(m_sound);
			appContext.eventManager.InvokeEvent(event);
			m_onClick();
			return;
		}

	}

	Button::CheckAndUpdate(mousePosition, appContext);
}

Rectangle ClassicButton::GetCollider() const {
	return m_collider;
}
