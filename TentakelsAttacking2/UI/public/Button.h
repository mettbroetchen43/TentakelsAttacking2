//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include "UIElement.h"
#include <string>
#include <functional>

class Button : public UIElement {
private:
	enum class State {
		ENABLED,
		HOVER,
		PRESSED,
		DISABLED,
	};
	std::string m_file;
	Texture2D m_texture;
	Rectangle m_textureRec;
	Rectangle m_collider;
	State m_state = State::ENABLED;
	int m_buttonParts = 4;

	int m_textSize = 24;
	std::string m_text;
	Vector2 m_textPosition;

	SoundType m_sound;

	std::function<void()> m_onClick;

	void SetTextSizeAndPosition(Vector2 resolution);
	[[nodiscard]] bool IsSameState(State state) const;

public:
	Button(std::string const& file, Vector2 pos, Vector2 size, Vector2 resolution, std::string const& text, SoundType releaseSound, std::function<void()> onClick);
	~Button() override;
	Button(Button const&) = delete;
	Button(Button&&) = default;
	Button& operator= (Button const&) = delete;
	Button& operator= (Button&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render() override;
	void Resize(Vector2 resolution) override;

	void SetEnabled(bool enabled);
	[[nodiscard]] bool IsEnabled() const;
};
