//
// Purpur Tentakel
// 15.08.2022
//

#pragma once
#include <string>
#include <functional>
#include <raylib.h>



class Button {
private:
	enum class State {
		CLEAR,
		HOVER,
		PRESSED,
	};
	std::string m_file;
	Texture2D m_texture;
	Rectangle m_textureRec;
	Rectangle m_colider;
	State m_state = State::CLEAR;
	int m_buttonParts = 4;

	int m_textSize = 24;
	std::string m_text;
	Vector2 m_textPosition;

	std::function<void()> m_onClick;

public:
	Button(std::string const& file, float posX, float posY, std::string const& text, std::function<void()> onClick);
	~Button();
	Button(Button const&) = delete;
	Button(Button&&) = default;
	Button& operator= (Button const&) = delete;
	Button& operator= (Button&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition);
	void Render();
};