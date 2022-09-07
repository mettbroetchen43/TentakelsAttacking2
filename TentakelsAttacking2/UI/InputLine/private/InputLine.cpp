//
// Purpur Tentakel
// 06.09.2022
//

#include "InputLine.h"
#include "Events.h"
#include "AppContext.h"
#include <string>

bool InputLine::AddChar(int key) {
	bool validAdd = m_charLimit > m_input.size();

	if (validAdd) {
		m_input += static_cast<char>(key);
	}

	return validAdd;
}
void InputLine::RemoveChar() {
	if (m_input.size() != 0) {
		m_input.pop_back();
	}
}
bool InputLine::IsAnyKeyPressed() {
	int key = GetKeyPressed();
	bool valid = (key >= 32 and key <= 126) or
		(key >= 320 and key <= 329) or
		key == 330;

	return valid;
}

std::string InputLine::GetPritableInput(std::string const& enter, std::string const& prefix, int fontSize,
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

std::string InputLine::GetPritablePlaceholder(std::string const& prefix, int fontSize, int cursorOffset) const {
	cursorOffset += 5; // Just to make shure that the curor didnt bounce out

	if (MeasureText(m_placeholderText.c_str(), fontSize) + cursorOffset < m_collider.width) {
		return m_placeholderText;
	}

	std::string toReturn = m_placeholderText;
	std::string toCheck = prefix + m_placeholderText;

	while (MeasureText(toCheck.c_str(), fontSize) + cursorOffset >= m_collider.width) {
		toReturn = toReturn.substr(0, toReturn.size()-1);
		toCheck = prefix + toReturn;
	}

	return  toReturn + prefix;
}

InputLine::InputLine(unsigned int focusID, Texture2D* texture, Vector2 pos, Vector2 size,
	unsigned int charLimit, Vector2 resolution)
	: UIElement(pos, size), Focusable(focusID), m_charLimit(charLimit), m_texture(texture) {
	m_collider = { resolution.x * pos.x, resolution.y * pos.y, resolution.x * size.x, resolution.y * size.y };
}

void InputLine::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
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
void InputLine::Render() {
	Rectangle textureRec = { 0.0f,0.0f,m_texture->width, m_texture->height };

	DrawTexturePro(*m_texture, textureRec, m_collider, Vector2(0.0f, 0.0f), 0, WHITE);
	DrawRectangleLines(m_collider.x, m_collider.y, m_collider.width, m_collider.height, WHITE);

	int posX = m_collider.x + 10;
	int posY = m_collider.y + m_collider.height * 0.1;
	int fontSize = m_collider.height * 0.8;
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
			DrawText(enter.c_str(), posX + cursorOffset + textLength, posY + m_collider.height * 0.05, fontSize, PURPLE);
		}
	}
}
void InputLine::Resize(Vector2 resolution) {
	m_collider = { resolution.x * m_pos.x, resolution.y * m_pos.y,
		resolution.x * m_size.x, resolution.y * m_size.y };
}

void InputLine::SetPlaceholderText(std::string placeholderText) {
	m_placeholderText = placeholderText;
}

Rectangle InputLine::GetCollider() const {
	return m_collider;
}
