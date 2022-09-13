//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "UIElement.h"
#include <string>
#include <functional>

class Button : public UIElement {
protected:
	enum class State {
		ENABLED,
		HOVER,
		PRESSED,
		DISABLED,
	};
	bool m_isPressed = false;
	Texture2D* m_texture;
	Rectangle m_textureRec;
	Rectangle m_collider;
	State m_state = State::ENABLED;
	int m_buttonParts = 4;

	int m_textSize = 24;
	std::string m_text;
	Vector2 m_textPosition;

	SoundType m_sound;

	std::function<void()> m_onClick = []() {};
	std::function<void()> m_onPress = []() {};

	void SetTextSizeAndPosition(Vector2 resolution);
	[[nodiscard]] bool IsSameState(State state) const;

public:
	Button(Texture2D* texture, Vector2 pos, Vector2 size, Vector2 resolution, std::string const& text,
		SoundType releaseSound);
	Button(Button const&) = default;
	Button(Button&& old) = default;
	Button& operator= (Button const&) = default;
	Button& operator= (Button&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetOnClick(std::function<void()> onClick);
	void SetOnPress(std::function<void()> onPress);

	void SetEnabled(bool enabled);
	[[nodiscard]] bool IsEnabled() const;
	[[nodiscard]] Rectangle GetCollider() const;
	void SetCollider(Rectangle collider);
};
