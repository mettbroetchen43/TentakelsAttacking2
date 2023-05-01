//
// Purpur Tentakel
// 23.04.2023
//

/*
	// trim string value
	adaptive sizes in not scrollable
	check if sizes in scrollable are still working

	scroll bar

	change button trigger in Popup
*/

#include "HPrint.h"
#include "HInput.h"
#include "HColors.h"
#include "UIEvents.hpp"
#include "AppContext.h"
#include "AbstractTableCell2.h"
#pragma once

template <typename T>
class TableCell2 final : public AbstactTableCell2 {
private:
	T m_value; ///< contains the value
	std::string m_stringValue; ///< contains the value as string
	std::function<void(TableCell2*, T, T)> m_updated = [](TableCell2*, T, T) {}; ///< conains a lambda that provides that the value has chanced
	
	/**
	 * Sets the value as string.
	 */
	void SetStringValue() {
		m_stringValue = std::to_string(m_value);
	}

	/**
	 * updates the cell value.
	 */
	void UpdateValue(T newValue) {
		T oldValue = m_value;
		m_value = newValue;
		SetStringValue();
		m_updated(this, oldValue, m_value);
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
	void Clicked(Vector2 const&, AppContext const& appContext) override {

		if (not IsEditable()) { return; }

		auto event = ShowCellPopUpEvent<T>(
			"Edit Entry",
			m_value,
			[this](T value) {this->UpdateValue(value); }
		);
		appContext.eventManager.InvokeEvent(event);
	}
	/**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the cell.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext const& appContext) override {
		if (not IsEditable()) { return; }

		bool shouldEdit = false;

		if (IsFocused()) {
			if (IsConfirmInputPressed()) {
				shouldEdit = true;
			}
		}

		if (shouldEdit) {
			auto event = ShowCellPopUpEvent<T>(
				"Edit Entry",
				m_value,
				[this](T value) {this->UpdateValue(value); }
			);
			appContext.eventManager.InvokeEvent(event);
		}


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
	/**
	 * returns the current value.
	 */
	[[nodiscard]] std::any GetValue() const override {
		return m_value;
	}
	/**
	 * returns the current value as string.
	 */
	[[nodiscard]] std::string GetValueAsString() const override {
		return m_stringValue;
	}
};

/**
 * overload because std::string has no overload for string.
 */
template<>
inline void TableCell2<std::string>::SetStringValue() {
	m_stringValue = m_value;
}
/**
 * overload because color has no string representation.
 */
template<>
inline void TableCell2<Color>::SetStringValue() {
	m_stringValue = Colors::AsString(m_value);
}

/**
 * overload because color is rendered dirfferent.
 */
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
