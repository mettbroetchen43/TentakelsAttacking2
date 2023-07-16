//
// Purpur Tentakel
// 16.07.2023
//

#pragma once
#include "Button.h"
#include "Focusable.h"

class ToggleButton : public Button, public Focusable {
private:
	bool m_isToggled{ false }; ///< contains the button is currently toggled

	std::function<void(bool)> m_onToggle{ [](bool) { } }; ///< contains the callback for the toggle

	/**
	 * updates the button state.
	 */
	void UpdateState();

public:
	/**
	 * ctor
	 */
	ToggleButton(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution, std::string const& text, SoundType releaseSound);

	/**
	 * logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

	/**
	 * return current collider of the button.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;
	/**
	 * returns if the current elements is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;

	/**
	 * returns if the button is current toggled.
	 */
	[[nodiscard]] bool IsToggled() const;
	/**
	 * sets the toggle state of the button.
	 */
	void SetToggleButton(bool isToggled);

	/**
	 * sets the toggle callback
	 */
	void SetOnToggle(std::function<void(bool)> onToggle);
};