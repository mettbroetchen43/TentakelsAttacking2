//
// Purpur Tentakel
// 23.04.2023
//


#include "AbstactTableCell2.h"
#include "AppContext.h"
#include "HPrint.h"
#pragma once

template <typename T>
class TableCell2 final : public AbstactTableCell2 {
private:
	T m_value;
	std::string m_stringValue;

	/**
	 * Sets the value as string.
	 */
	void SetStringValue() {
		m_stringValue = std::to_string(m_value);
	}

public:
	/**
	 * ctor
	 */
	TableCell2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID, T value)
		: AbstactTableCell2(pos, size, alignment, resolution, focusID), m_value(value) {
		SetStringValue();
		CalculateTextSize();
	}

	/**
	 * use this if the cell is clicked.
	 * need to be implemented by every cell.
	 */
	void Clicked(Vector2 const& mousePosition, AppContext const& appContext) override {

		if (not IsEditable()) { return; }
		AbstactTableCell2::Clicked(mousePosition, appContext);
	}
	/**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the cell.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override {
		AbstactTableCell2::CheckAndUpdate(mousePosition, appContext);
	}
	/**
	 * renders the cell
	 */
	void Render(AppContext const& appContext) override {
		AbstactTableCell2::Render(appContext);

		DrawTextEx(
			*appContext.assetManager.GetFont(),
			m_stringValue.c_str(),
			m_textPosition,
			m_textSize,
			0.0f,
			WHITE
		);
	}

	/**
	 * calculates a new text size from the collider.
	 */
	void CalculateTextSize() override {
		m_textSize = m_collider.height / 3;
		m_textPosition = { m_collider.x + m_collider.width * 0.05f ,m_collider.y + m_textSize };
	}
};

template<>
inline void TableCell2<std::string>::SetStringValue() {
	m_stringValue = m_value;
}
template<>
inline void TableCell2<Color>::SetStringValue() {
	m_stringValue = "Color";
}

template<>
inline void TableCell2<Color>::Render(AppContext const& appContext) {
	AbstactTableCell2::Render(appContext);

	int offset = static_cast<int>(m_collider.height / 10);
	DrawRectangle(
		static_cast<int>(m_collider.x + offset),
		static_cast<int>(m_collider.y + offset),
		static_cast<int>(m_collider.width - 2 * offset),
		static_cast<int>(m_collider.height - 2 * offset),
		m_value
	);
}