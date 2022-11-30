//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "UIElement.hpp"
#include <string>
#include <functional>

/**
 * base buton class
 * 
 */
class Button : public UIElement {
protected:
	enum class State { ///< contains the possible button states
		ENABLED,
		HOVER,
		PRESSED,
		DISABLED,
	};
	bool m_isPressed = false; ///< contans if the button is currently pressed
	Texture2D* m_texture; ///< contains a ponter of the btn texture
	Rectangle m_textureRec; ///< defines a rectangle on the texture that will be renderd
	State m_state = State::ENABLED; ///< contains the current button state
	int m_buttonParts = 4; ///< defines in how many parts the texture gets split

	float m_textSize = 24.0f; ///< defines the textheight in px
	std::string m_text; ///< contains the text on the button
	Vector2 m_textPosition; ///< contains the position of the text

	SoundType m_sound; ///< contains the release sound of the button

	std::function<void()> m_onClick = []() {}; ///< contains a lambda that gets called if the button is down
	std::function<void()> m_onPress = []() {}; ///< contains a lambda that gets called if the button is released

	/**
	 * calculates the text size and position.
	 */
	void SetTextSizeAndPosition(AppContext const& appContext);
	/**
	 * checks if the provided state is the same as the current state.
	 */
	[[nodiscard]] bool IsSameState(State state) const;

	/**
	 * calls UpdateCollider from the UIElement.
	 * updated the text position and size.
	 */
	void UpdateCollider() override;

public:
	/**
	 * ctor.
	 * initialize and calls text calculating.
	 */
	Button(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& text, SoundType releaseSound);
	Button();
	Button(Button const&) = default;
	Button(Button&& old) = default;
	Button& operator= (Button const&) = default;
	Button& operator= (Button&&) = default;

	/**
	 * complete logic og the button.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * rendres the button.
	 */
	void Render(AppContext const& appContext) override;
	/**
	 * calls resize from UIElement.
	 * resizes the text.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	/**
	 * sets the onClick lambda that is called when the button gets released.
	 */
	void SetOnClick(std::function<void()> onClick);
	/**
	 * sets the onPress lambda that is called when the button is down.
	 */
	void SetOnPress(std::function<void()> onPress);

	/**
	 * sets a new button text and calculates the new text height.
	 */
	void SetText(std::string const& text);
	/**
	 * returns the current text.
	 */
	[[nodiscard]] std::string GetText() const;

	/**
	 * sets wether the button is enabled or not.
	 */
	void SetEnabled(bool enabled);
	/**
	 * returns if the button is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const;

	/**
	 * sets a new colider.
	 * calls the UIElement and resets text position.
	 */
	void SetCollider(Rectangle collider) override;
	
	/**
	 * sets a new position and resets the text position,
	 */
	void SetPosition(Vector2 pos) override;
};
