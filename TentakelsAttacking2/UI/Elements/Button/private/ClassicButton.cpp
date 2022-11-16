//
// Purpur Tentakel
// 04.09.2022
//

#include "ClassicButton.h"
#include "AppContext.h"
#include "HInput.h"

ClassicButton::ClassicButton(unsigned int focusID, Vector2 pos, Vector2 size,
	Alignment allignment, Vector2 resolution, std::string const& text,
	SoundType releaseSound)
	: Focusable(focusID), Button(pos, size, allignment, text,
		releaseSound, resolution) { }

[[nodiscard]] bool ClassicButton::IsEnabled() const{
	return m_state != State::DISABLED;
};

void ClassicButton::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	if (IsSkipInput()) { return; }

	if (IsFocused()) {
		if (m_state == State::DISABLED) {
			if (IsConfirmInputPressed()) {
				auto event = PlaySoundEvent(SoundType::CLICKED_DISABLED_STD);
				appContext.eventManager.InvokeEvent(event);
				return;
			}

			bool disabledAction =
				IsConfirmInputDown()
				or IsConfirmInputReleased();
			if (disabledAction) {
				return;
			}
		}

		if (IsConfirmInputPressed()) {
			if (m_state != State::PRESSED) {
				m_state = State::PRESSED;
				m_isPressed = true;
				auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
				appContext.eventManager.InvokeEvent(event);
				return;
			}
		}

		if (IsConfirmInputDown()) {
			m_state = State::PRESSED;
			m_onPress();
			return;
		}

		if (IsConfirmInputReleased()) {
			bool hover = CheckCollisionPointRec(mousePosition, m_colider);
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
	return m_colider;
}
