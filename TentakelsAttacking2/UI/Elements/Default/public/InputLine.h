//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "UIElement.h"
#include "Focusable.h"
#include <raylib.h>
#include <string>
#include <functional>

template <class T>
class InputLine : public UIElement, public Focusable {
protected:
	unsigned int m_charLimit;
	Rectangle m_collider;
	std::string m_value;
	std::string m_oldValue;
	std::string m_placeholderText;
	Texture* m_texture;
	double m_backspacePressTime = 0.0;
	std::function<void()> m_onEnter = []() {};

	bool AddChar(int key) {
		bool validAdd = m_charLimit > m_value.size();

		if (validAdd) {
			m_value += static_cast<char>(key);
		}

		return validAdd;
	}
	void RemoveChar() {
		if (m_value.size() != 0) {
			m_value.pop_back();
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
	[[nodiscard]] std::string GetPritableInput(std::string const& enter, std::string const& prefix,
		float fontSize, int cursorOffset, AppContext const& appContext) const {
		cursorOffset += 5; // Just to make shure that the curor didnt bounce out

		Vector2 textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			(m_value + enter).c_str(),
			fontSize,
			0.0f);
		if (textSize.x + cursorOffset < m_collider.width) {
			return m_value;
		}

		std::string toReturn = m_value;
		std::string toCheck = prefix + m_value + enter;

		do {
			toReturn = toReturn.substr(1, toReturn.size());
			toCheck = prefix + toReturn + enter;
			textSize = MeasureTextEx(
				*(appContext.assetManager.GetFont()),
				toCheck.c_str(),
				fontSize,
				0.0f);
		} while (textSize.x + cursorOffset >= m_collider.width);

		return prefix + toReturn;
	}
	[[nodiscard]] std::string GetPritablePlaceholder(std::string const& prefix, float fontSize,
		int cursorOffset, AppContext const& appContext) const {
		cursorOffset += 5; // Just to make shure that the curor didnt bounce out

		Vector2 textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			m_placeholderText.c_str(),
			fontSize,
			0.0f);
		if (textSize.x + cursorOffset < m_collider.width) {
			return m_placeholderText;
		}

		std::string toReturn = m_placeholderText;
		std::string toCheck = prefix + m_placeholderText;

		do {
			toReturn = toReturn.substr(0, toReturn.size() - 1);
			toCheck = prefix + toReturn;
			textSize = MeasureTextEx(
				*(appContext.assetManager.GetFont()),
				toCheck.c_str(),
				fontSize,
				0.0f);
		} while (textSize.x + cursorOffset >= m_collider.width);

		return  toReturn + prefix;
	}

public:
	InputLine(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		unsigned int charLimit, Texture2D* texture, Vector2 resolution)
		: UIElement(pos, size, alignment), Focusable(focusID), m_charLimit(charLimit), m_texture(texture) {
		m_collider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
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
			auto event = SelectFocusElementEvent(this);
			appContext.eventManager.InvokeEvent(event);
		}

		if (!IsFocused()) { return; }

		if (IsKeyPressed(KEY_ENTER)) {
			m_onEnter();
		}

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

		while (true) {
		int key = GetCharPressed();

			if (key <= 0) { return; }

			if (!IsValidKey(key)) { continue; }

			if (!AddChar(key)) {
				auto event = ShowMessagePopUpEvent("Max Input", "Maximum number of input values reached");
				appContext.eventManager.InvokeEvent(event);
				return;
			}
		}
	}
	void Render(AppContext const& appContext) override {
		// Update here to make shure its after call of HasValueChanced();
		m_oldValue = m_value;

		Rectangle textureRec = { 
			0.0f,
			0.0f,
			static_cast<float>(m_texture->width), 
			static_cast<float>(m_texture->height) 
		};

		DrawTexturePro(*m_texture, textureRec,	m_collider,	Vector2(0.0f, 0.0f), 0,	WHITE);

		DrawRectangleLines(static_cast<int>(m_collider.x), static_cast<int>(m_collider.y),
			static_cast<int>(m_collider.width), static_cast<int>(m_collider.height), WHITE);

		float posX = m_collider.x + 10.0f;
		float posY = m_collider.y + m_collider.height * 0.1f;
		float fontSize = m_collider.height * 0.8f;
		int cursorOffset = 1;

		std::string enter = "_";
		std::string prefix = "...";
		std::string printableInput;

		if (m_value.size() > 0) {
			printableInput = GetPritableInput(enter, prefix, fontSize, cursorOffset, appContext);
			DrawTextEx(
				*(appContext.assetManager.GetFont()),
				printableInput.c_str(),
				Vector2(posX, posY),
				fontSize,
				0,
				WHITE);
		}
		else {
			std::string printablePlaceholder = GetPritablePlaceholder(prefix, fontSize, cursorOffset, appContext);
			DrawTextEx(
				*(appContext.assetManager.GetFont()),
				printablePlaceholder.c_str(),
				Vector2(posX, posY),
				fontSize,
				0,
				GRAY);
		}


		if (IsFocused()) {
			size_t time = static_cast<size_t>(GetTime() * 2.0);
			Vector2 textLength = MeasureTextEx(
				*(appContext.assetManager.GetFont()),
				printableInput.c_str(),
				fontSize,
				0.0f);

			if (time % 2 == 0) {
				DrawTextEx(
					*(appContext.assetManager.GetFont()),
					enter.c_str(),
					Vector2(posX + cursorOffset + textLength.x, posY + m_collider.height * 0.05f),
					fontSize,
					0,
					PURPLE);
			}
		}
	}
	void Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) override {
		m_collider = { resolution.x * m_pos.x, resolution.y * m_pos.y,
			resolution.x * m_size.x, resolution.y * m_size.y };
	}

	void SetPlaceholderText(std::string placeholderText) {
		m_placeholderText = placeholderText;
	}
	void SetValue(T value) {
		m_value = std::to_string(value);
	}
	[[nodiscard]] T GetValue() = delete;

	[[nodiscard]] Rectangle GetCollider() const override {
		return m_collider;
	}
	[[nodiscard]] bool HasValueChanced() const {
		return m_value == m_oldValue;
	}
	void SetOnEnter(std::function<void()> onEnter) {
		m_onEnter = onEnter;
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
		if (m_value.size() == 0) {
			valid = false;
		}

		for (char c : m_value) {
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
	return std::stoi(m_value);
}
template<>
[[nodiscard]] double InputLine<double>::GetValue() {
	std::string toReturn = m_value;
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
	return m_value;
}

// need because std::to_string() has so overload for std::string
template<>
void InputLine<std::string>::SetValue(std::string value) {
	m_value = value;
}

