//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include "AppContext.h"
#include "HTextProcessing.h"
#include "HTextProcecingConstant.hpp"
#include <raylib.h>
#include <string>
#include <functional>

template <class T>
class InputLine : public UIElement, public Focusable {
protected:
	unsigned int m_charLimit;
	Rectangle m_colider;
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

			auto event = PlaySoundEvent(SoundType::TEXT);
			AppContext::GetInstance().eventManager.InvokeEvent(event);
		}

		return validAdd;
	}
	void RemoveChar() {
		if (m_value.size() != 0) {
			m_value.pop_back();

			auto event = PlaySoundEvent(SoundType::TEXT);
			AppContext::GetInstance().eventManager.InvokeEvent(event);
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

public:
	InputLine(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		unsigned int charLimit, Vector2 resolution)
		: UIElement(pos, size, alignment), Focusable(focusID), m_charLimit(charLimit) {
		m_texture = AppContext::GetInstance().assetManager.GetTexture(AssetType::GREY);
		m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	}
	InputLine(InputLine const&) = default;
	InputLine(InputLine&&) = default;
	InputLine& operator= (InputLine const&) = default;
	InputLine& operator= (InputLine&&) = default;

	[[nodiscard]] virtual bool IsEnabled() const override {
		return true;
	}

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override {
		bool hover = CheckCollisionPointRec(mousePosition, m_colider);
		bool validSelect = !IsFocused() and
			hover and IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

		if (validSelect) {
			auto event = SelectFocusElementEvent(this);
			appContext.eventManager.InvokeEvent(event);
		}

		if (!IsFocused()) { return; }

		if (IsKeyPressed(KEY_ENTER) or IsKeyPressed(KEY_KP_ENTER)) {
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

		DrawTexturePro(
			*m_texture,
			textureRec,
			m_colider,
			Vector2(0.0f, 0.0f),
			0.0f,
			WHITE
		);

		DrawRectangleLinesEx(
			m_colider,
			2.0f,
			PURPLE
		);

		float posX = m_colider.x + 10.0f;
		float posY = m_colider.y + m_colider.height * 0.1f;
		float fontSize = m_colider.height * 0.8f;
		std::string printableInput;

		if (m_value.size() > 0) {
			printableInput = GetPritableTextInColider(
				m_value,
				fontSize,
				m_colider,
				appContext
			);
			DrawTextEx(
				*(appContext.assetManager.GetFont()),
				printableInput.c_str(),
				Vector2(posX, posY),
				fontSize,
				0,
				WHITE
			);
		}
		else {
			std::string printablePlaceholder = GetPritablePlaceholderTextInColider(
				m_placeholderText,
				fontSize,
				m_colider,
				appContext
			);
			DrawTextEx(
				*(appContext.assetManager.GetFont()),
				printablePlaceholder.c_str(),
				Vector2(posX, posY),
				fontSize,
				0,
				GRAY
			);
		}


		if (IsFocused()) {
			size_t time = static_cast<size_t>(GetTime() * 2.0);
			Vector2 textLength = MeasureTextEx(
				*(appContext.assetManager.GetFont()),
				printableInput.c_str(),
				fontSize,
				0.0f
			);

			if (time % 2 == 0) {
				DrawTextEx(
					*(appContext.assetManager.GetFont()),
					&Constants::c_enter,
					Vector2(
						posX + Constants::c_cursorOffset + textLength.x,
						posY + m_colider.height * 0.05f
					),
					fontSize,
					0,
					PURPLE
				);
			}
		}
	}
	void Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) override {
		m_colider = { resolution.x * m_pos.x, resolution.y * m_pos.y,
			resolution.x * m_size.x, resolution.y * m_size.y };
	}

	void SetPlaceholderText(std::string placeholderText) {
		m_placeholderText = placeholderText;
	}
	void SetValue(T value) {
		m_value = std::to_string(value);
	}
	[[nodiscard]] T GetValue() = delete;
	void Clear() {
		m_value.clear();
	}

	[[nodiscard]] Rectangle GetCollider() const override {
		return m_colider;
	}
	[[nodiscard]] bool HasValue() const {
		return !m_value.empty();
	}
	[[nodiscard]] bool HasValueChanced() const {
		return m_value != m_oldValue;
	}
	void SetOnEnter(std::function<void()> onEnter) {
		m_onEnter = onEnter;
	}
};

template<>
inline bool InputLine<int>::IsValidKey(int key) {
	bool valid = key >= 48 and
		key <= 57;

	return valid;
}
template<>
inline bool InputLine<float>::IsValidKey(int key) {
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
inline bool InputLine<double>::IsValidKey(int key) {
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
inline bool InputLine<std::string>::IsValidKey(int key) {
	bool valid = key >= 32 and
		key <= 126;

	return valid;
}

template<>
[[nodiscard]] inline int InputLine<int>::GetValue() {
	StripString(m_value);
	if (m_value.size() == 0) {
		return 0;
	}
	return std::stoi(m_value);
}
template<>
[[nodiscard]] inline float InputLine<float>::GetValue() {
	StripString(m_value);
	if (m_value.size() == 0) {
		return 0.0f;
	}
	for (char& c : m_value) {
		if (c == ',') {
			c = '.';
			break;
		}
	}
	return std::stof(m_value);
}
template<>
[[nodiscard]] inline double InputLine<double>::GetValue() {
	StripString(m_value);
	if (m_value.size() == 0) {
		return 0.0;
	}
	for (char& c : m_value) {
		if (c == ',') {
			c = '.';
			break;
		}
	}
	return std::stod(m_value);
}
template<>
[[nodiscard]] inline std::string InputLine<std::string>::GetValue() {
	StripString(m_value);
	return m_value;
}

// need because std::to_string() has so overload for std::string
template<>
inline void InputLine<std::string>::SetValue(std::string value) {
	m_value = value;
}
