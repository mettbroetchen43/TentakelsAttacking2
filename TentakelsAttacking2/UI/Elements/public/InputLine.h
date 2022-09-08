//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "UIElement.h"
#include "Focusable.h"
#include <raylib.h>
#include <string>

template <class T>
class InputLine : public UIElement, public Focusable {
protected:
	unsigned int m_charLimit;
	Rectangle m_collider;
	std::string m_input;
	std::string m_placeholderText;
	Texture* m_texture;
	double m_backspacePressTime = 0.0;

	bool AddChar(int key) {
		bool validAdd = m_charLimit > m_input.size();

		if (validAdd) {
			m_input += static_cast<char>(key);
		}

		return validAdd;
	}
	void RemoveChar() {
		if (m_input.size() != 0) {
			m_input.pop_back();
		}
	}
	[[nodiscard]] bool IsAnyKeyPressed() {
		int key = GetKeyPressed();
		bool valid = (key >= 32 and key <= 126) or
			(key >= 320 and key <= 329) or
			key == 330;

		return valid;
	}
	[[nodiscard]] bool IsValidKey(int key) = delete;
	[[nodiscard]] std::string GetPritableInput(std::string const& enter, std::string const& prefix, int fontSize,
		int cursorOffset) const {
		cursorOffset += 5; // Just to make shure that the curor didnt bounce out

		if (MeasureText((m_input + enter).c_str(), fontSize) + cursorOffset < m_collider.width) {
			return m_input;
		}

		std::string toReturn = m_input;
		std::string toCheck = prefix + m_input + enter;

		while (MeasureText(toCheck.c_str(), fontSize) + cursorOffset >= m_collider.width) {
			toReturn = toReturn.substr(1, toReturn.size());
			toCheck = prefix + toReturn + enter;
		}

		return prefix + toReturn;
	}
	[[nodiscard]] std::string GetPritablePlaceholder(std::string const& prefix, int fontSize, int cursorOffset) const {
		cursorOffset += 5; // Just to make shure that the curor didnt bounce out

		if (MeasureText(m_placeholderText.c_str(), fontSize) + cursorOffset < m_collider.width) {
			return m_placeholderText;
		}

		std::string toReturn = m_placeholderText;
		std::string toCheck = prefix + m_placeholderText;

		while (MeasureText(toCheck.c_str(), fontSize) + cursorOffset >= m_collider.width) {
			toReturn = toReturn.substr(0, toReturn.size() - 1);
			toCheck = prefix + toReturn;
		}

		return  toReturn + prefix;
	}

public:
	InputLine(unsigned int focusID, Texture2D* texture, Vector2 pos, Vector2 size, unsigned int charLimit,
		Vector2 resolution)
		: UIElement(pos, size), Focusable(focusID), m_charLimit(charLimit), m_texture(texture) {
		m_collider = { resolution.x * pos.x, resolution.y * pos.y, resolution.x * size.x, resolution.y * size.y };
	}
	InputLine(InputLine const&) = default;
	InputLine(InputLine&&) = default;
	InputLine& operator= (InputLine const&) = default;
	InputLine& operator= (InputLine&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override {
		bool hover = CheckCollisionPointRec(mousePosition, m_collider);
		bool validSelect = !IsFocused() and
			hover and IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

		if (validSelect) {
			auto event = SelectFocusEvent(this);
			appContext.eventManager.InvokeEvent(event);
		}

		if (!IsFocused()) { return; }

		if (IsKeyPressed(KEY_BACKSPACE)) {
			RemoveChar();
			m_backspacePressTime = GetTime();
			return;
		}

		if (IsKeyDown(KEY_BACKSPACE)) {
			if (m_backspacePressTime < GetTime() - 0.5) {
				RemoveChar();
				return;
			}
		}

		if (!IsAnyKeyPressed()) { return; }

		int key = GetCharPressed();
		while (key > 0) {
			if (!IsValidKey(key)) {
				key = GetKeyPressed();
				continue;
			}

			if (!AddChar(key)) {
				// Popup Event -> TODO
			}

			key = GetKeyPressed();
		}
	}
	void Render() override {
		Rectangle textureRec = { 
			0.0f,
			0.0f,
			static_cast<float>(m_texture->width), 
			static_cast<float>(m_texture->height) 
		};

		DrawTexturePro(*m_texture, textureRec,	m_collider,	Vector2(0.0f, 0.0f), 0,	WHITE);

		DrawRectangleLines(static_cast<int>(m_collider.x), static_cast<int>(m_collider.y),
			static_cast<int>(m_collider.width), static_cast<int>(m_collider.height), WHITE);

		int posX = static_cast<int>(m_collider.x) + 10;
		int posY = static_cast<int>(m_collider.y + m_collider.height * 0.1);
		int fontSize = static_cast<int>(m_collider.height * 0.8);
		int cursorOffset = 8;

		std::string enter = "_";
		std::string prefix = "...";
		std::string printableInput;

		if (m_input.size() > 0) {
			printableInput = GetPritableInput(enter, prefix, fontSize, cursorOffset);
			DrawText(printableInput.c_str(), posX, posY, fontSize, WHITE);
		}
		else {
			std::string printablePlaceholder = GetPritablePlaceholder(prefix, fontSize, cursorOffset);
			DrawText(printablePlaceholder.c_str(), posX, posY, fontSize, GRAY);
		}


		if (IsFocused()) {
			int time = static_cast<int>(GetTime());
			int textLength = MeasureText(printableInput.c_str(), fontSize);

			if (time % 2 == 0) {
				DrawText(enter.c_str(), posX + cursorOffset + textLength, posY + static_cast<int>(m_collider.height * 0.05), fontSize, PURPLE);
			}
		}
	}
	void Resize(Vector2 resolution) override {
		m_collider = { resolution.x * m_pos.x, resolution.y * m_pos.y,
			resolution.x * m_size.x, resolution.y * m_size.y };
	}

	void SetPlaceholderText(std::string placeholderText) {
		m_placeholderText = placeholderText;
	}
	void SetValue(T value) {
		m_input = std::to_string(T);
	}
	[[nodiscard]] T GetValue() = delete;

	[[nodiscard]] Rectangle GetCollider() const override {
		return m_collider;
	}
};

template<>
bool InputLine<int>::IsValidKey(int key) {
	bool valid = key >= 48 and
		key <= 57;

	return valid;
}
template<>
bool InputLine<double>::IsValidKey(int key) {
	bool valid = (key >= 48 and key <= 57) // numbers
		or key == 44 // comma
		or key == 46; // dot

	//check for multiple commas/dots
	if ('.' == key or ',' == key) {
		if (m_input.size() == 0) {
			valid = false;
		}

		for (char c : m_input) {
			if ('.' == c or ',' == c) {
				valid = false;
				break;
			}
		}
	}

	return valid;
}
template<>
bool InputLine<std::string>::IsValidKey(int key) {
	bool valid = key >= 32 and
		key <= 126;

	return valid;
}

template<>
[[nodiscard]] int InputLine<int>::GetValue() {
	return std::stoi(m_input);
}
template<>
[[nodiscard]] double InputLine<double>::GetValue() {
	std::string toReturn = m_input;
	for (char& c : toReturn) {
		if (c == ',') {
			c = '.';
			break;
		}
	}
	return std::stod(toReturn);
}
template<>
[[nodiscard]] std::string InputLine<std::string>::GetValue() {
	return m_input;
}

