//
// Purpur Tentakel
// 16.07.2023
//

#include "ToggleButton.h"
#include "HInput.h"
#include "AppContext.h"

void ToggleButton::UpdateState() {
	if (   m_state == State::ENABLED
		or m_state == State::PRESSED ) { 
		m_state = m_isToggled ? State::PRESSED : State::ENABLED;
	}
}

ToggleButton::ToggleButton(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& text, SoundType releaseSound)
	: Button{ pos, size, alignment, resolution, text, releaseSound }, Focusable{ focusID } { }

void ToggleButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	switch (m_state){
		case State::DISABLED: {

			bool play{ false };
			
			if (CheckCollisionPointRec(mousePosition, m_collider) and
				IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) { play = true; }
			else if (IsFocused() and IsConfirmInputPressed()) { play = true; }

			if (play) {
				PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
				appContext.eventManager.InvokeEvent(event);
			}
			break;
		}

		case State::HOVER: {
			if (not CheckCollisionPointRec(mousePosition, m_collider)) {
				m_state = m_isToggled ? State::PRESSED : State::HOVER;
				break;
			}
			if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT)) {
				m_state = State::PRESSED;
			}
			else if (IsFocused() and IsConfirmInputPressed()){
				m_state = State::PRESSED;
			}
			break;
		}

		case State::ENABLED: {
			if (CheckCollisionPointRec(mousePosition, m_collider)) {
				m_state = State::HOVER;
			}
			break;
		}

		case State::PRESSED: {
			if (CheckCollisionPointRec(mousePosition, m_collider)) {
				if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
					m_isToggled = not m_isToggled;
					m_onToggle(m_isToggled);
					if (not IsConfirmInputDown()) {
						m_state = State::HOVER;
					}
				}
				if (IsFocused() and IsConfirmInputReleased()) {
					m_isToggled = not m_isToggled;
					m_onToggle(m_isToggled);
					if (not IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
						m_state = State::HOVER;
					}
				}
			} 
			else {
				if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
					if (not IsConfirmInputDown()) {
						m_state = State::HOVER;
					}
				}
				if (IsFocused() and IsConfirmInputReleased()) {
					if (not IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
						m_state = State::HOVER;
					}
				}
			}
			break;
		}

		default: {
			throw std::runtime_error("invalid toggle button state");
			break;
		}
	}
}

Rectangle ToggleButton::GetCollider() const {
	return m_collider;
}
bool ToggleButton::IsEnabled() const {
	return m_state != State::DISABLED;
}

bool ToggleButton::IsToggled() const {
	return m_isToggled;
}
void ToggleButton::SetToggleButton(bool isToggled) {
	m_isToggled = isToggled;
	UpdateState();
}

void ToggleButton::SetOnToggle(std::function<void(bool)> onToggle) {
	m_onToggle = onToggle;
}
