//
// Purpur Tentakel
// 29.09.22
//

#pragma once
#include "AbstractTableCell.h"
#include "AppContext.h"
#include "HTextProcessing.h"
#include <string>
#include <iostream>
#include <functional>

/**
 * provides a cell for the table call that can handle premitive datatypes.
 */
template<typename T>
class TableCell final : public AbstractTableCell {
protected:
	T m_value; ///< contains the current value

	std::function<void()> m_resizeCells = []() {}; ///< contains the resize lambda -> gets called to trigger the table to resize the sells
	std::function<void(TableCell*, T, T)> m_updated = [](TableCell*, T, T) {}; ///< conains a lambda that provides that the value has chanced

	Vector2 m_textPosition; ///< contains the value position
	float m_textSize; ///< contains the text size
	float m_textMargin; ///< contains the text margin on the left side
	Vector2 m_minSize; ///< contains the min size the cell needs
	Vector2 m_maxSize; ///< contains the max size the cell needs

	/**
	 * returns whether the cell meets the requirements for the content to be updated.
	 */
	[[nodiscard]] bool ShouldEdit(Vector2 const& mousePosition) const {
		bool edit = false;

		if (!m_editable) {
			return edit;
		}

		if (IsFocused()) {
			if (IsKeyPressed(KEY_ENTER)
				or IsKeyPressed(KEY_SPACE)) {
				edit = true;
			}
		}
		if (CheckCollisionPointRec(mousePosition, m_colider)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				edit = true;
			}
		}

		if (edit) {
			auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
			AppContext::GetInstance().eventManager.InvokeEvent(event);
		}

		return edit;
	}
	/**
	 * calctulates and returns the size the cell needs to display the value perfectly. 
	 */
	[[nodiscard]] Vector2 CalculateNeededSize(Vector2& textSize) const {
		textSize.x += 2 * m_textMargin;
		textSize.y += m_textSize;

		Vector2 neededSize = {
			(textSize.x / m_colider.width) * m_size.x,
			(textSize.y / m_colider.height) * m_size.y
		};

		ClampNeededSize(neededSize);

		return neededSize;
	}
	/**
	 * claps the calculated needed size between min and max.
	 */
	void ClampNeededSize(Vector2& neededSize) const {
		neededSize.x = neededSize.x < m_minSize.x ? m_minSize.x : neededSize.x;
		neededSize.x = neededSize.x > m_maxSize.x ? m_maxSize.x : neededSize.x;

		neededSize.y = neededSize.y < m_minSize.y ? m_minSize.y : neededSize.y;
		neededSize.y = neededSize.y > m_maxSize.y ? m_maxSize.y : neededSize.y;
	}

	/**
	 * update the value to the provided value and calls the cells to resize.
	 */
	void UpdateValue([[maybe_unused]] T value) {
		T oldValue = m_value;
		m_value = value;
		m_resizeCells();
		m_updated(this, oldValue, m_value);
	}

public:
	/**
	 * ctor.
	 * sets sizes.
	 */
	TableCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution,
		std::function<void()> resizeCells,
		std::function<void(TableCell*, T, T)> updated)
		: AbstractTableCell(ID, pos, size, alignment, resolution),
			m_resizeCells(resizeCells), m_updated(updated){

			m_minSize = {
				m_size.x / 2,
				m_size.y / 2
			};
			m_maxSize = {
				m_size.x * 2,
				m_size.y * 2
			};

			m_textSize = m_colider.height / 2;
			m_textMargin = m_colider.width / 20;
			m_textPosition = {
				m_colider.x + m_textMargin,
				m_colider.y + m_colider.height / 4
			};
	}

	/**
	 * cell logic.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override {
		if (!m_editable) {
			return;
		}

		if (CheckCollisionPointRec(mousePosition, m_colider)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				auto event = SelectFocusElementEvent(this);
				appContext.eventManager.InvokeEvent(event);
			}
		}

		if (ShouldEdit(mousePosition)) {
			auto event = ShowCellPopUpEvent<T>(
				"Edit Entry",
				m_value,
				[this](T value) {this->UpdateValue(value);}
			);
			appContext.eventManager.InvokeEvent(event);
		}
	}
	/**
	 * renders the cell.
	 */
	void Render(AppContext const& appContext) override {
		std::string printableValue = GetPritablePlaceholderTextInColider(
			std::to_string(m_value).c_str(),
			m_textSize,
			m_colider,
			appContext
		);
		DrawTextEx(
			*(appContext.assetManager.GetFont()),
			printableValue.c_str(),
			m_textPosition,
			m_textSize,
			0.0f,
			WHITE
		);

		DrawRectangleLinesEx(
			m_colider,
			3.0f,
			WHITE
		);
	}
	/**
	 * resizes the cell.
	 */
	void Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) override {
		
		UIElement::Resize(resolution, appContext);

		m_textSize = m_colider.height / 2;
		m_textPosition = {
		m_colider.x + m_colider.width / 20,
		m_colider.y + m_colider.height / 4
		};
	}

	/**
	 * returns the current value.
	 */
	[[nodiscard]] T GetValue() const {
		return m_value;
	};
	void SetValue(T value, bool resize = false) {
		m_value = value;
		
		if (resize) {
			m_resizeCells();
		}
	};

	/**
	 * calctulates and returns the size the cell needs to display the value perfectly.
	 */
	[[nodiscard]] virtual Vector2 GetNeededSize() override {
		Vector2 textSize = MeasureTextEx(
			*(AppContext::GetInstance().assetManager.GetFont()),
			std::to_string(m_value).c_str(),
			m_textSize,
			0.0f
		);

		return CalculateNeededSize(textSize);
	}
	
	[[nodiscard]] Rectangle GetCollider() const override {
		return UIElement::GetColider();
	}
};


/**
 * calctulates and returns the size the cell needs to display the value perfectly.
 * overloat is needed because std::to_string doesnt provide an overloat for std::string.
 */
template<>
[[nodiscard]] inline Vector2 TableCell<std::string>::GetNeededSize() {
	Vector2 textSize = MeasureTextEx(
		*(AppContext::GetInstance().assetManager.GetFont()),
		m_value.c_str(),
		m_textSize,
		0.0f
	);

	return CalculateNeededSize(textSize);
}
/**
 * returns the size for a color cell.
 * overlaot is needed because its not possible to measue the size of an color.
 */
template<>
[[nodiscard]] inline Vector2 TableCell<Color>::GetNeededSize() {
	Vector2 neededSize = { 0.05f, 0.1f };
	return neededSize;
}

/**
 * renders the string cell.
 * overloat is needed because std::to_string doesnt provide an overloat for std::string.
 */
template<>
inline void TableCell<std::string>::Render(AppContext const& appContext) {
	std::string printableValue = GetPritablePlaceholderTextInColider(
		m_value.c_str(),
		m_textSize,
		m_colider,
		appContext
	);
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		printableValue.c_str(),
		m_textPosition,
		m_textSize,
		0.0f,
		WHITE
	);

	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);
}

/**
 * renders the color cell.
 * overloat is needed because std::to_string doesnt provide an overloat for a color.
 */
template<>
inline void TableCell<Color>::Render([[maybe_unused]]AppContext const& appContext) {
	float spacing = 5.0f;
	Rectangle toFill = {
		 m_colider.x + spacing,
		 m_colider.y + spacing,
		 m_colider.width - 2 * spacing,
		 m_colider.height - 2 * spacing
	};
	DrawRectanglePro(
		toFill,
		Vector2(0.0f, 0.0f),
		0.0f,
		m_value
	);

	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);
}