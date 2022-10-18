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

template<typename EntryType>
class TableCell : public AbstractTableCell {
protected:
	EntryType m_value;

	std::function<void()> m_resizeCells = []() {};
	std::function<void(TableCell*)> m_updated = [](TableCell*) {};

	Vector2 m_textPosition;
	float m_textSize;
	float m_textMargin;
	Vector2 m_minSize;
	Vector2 m_maxSize;

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
	void ClampNeededSize(Vector2& neededSize) const {
		neededSize.x = neededSize.x < m_minSize.x ? m_minSize.x : neededSize.x;
		neededSize.x = neededSize.x > m_maxSize.x ? m_maxSize.x : neededSize.x;

		neededSize.y = neededSize.y < m_minSize.y ? m_minSize.y : neededSize.y;
		neededSize.y = neededSize.y > m_maxSize.y ? m_maxSize.y : neededSize.y;
	}

	void UpdateValue([[maybe_unused]] EntryType value) {
		m_value = value;
		m_resizeCells();
		m_updated(this);
	}

public:
	TableCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution,
		std::function<void()> resizeCells,
		std::function<void(TableCell*)> updated) 
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
			auto event = ShowCellPopUpEvent<EntryType>(
				"Edit Entry",
				m_value,
				[&](EntryType value) {UpdateValue(value);}
			);
			appContext.eventManager.InvokeEvent(event);
		}
	}
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
	void Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) override {
		m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
		};
		m_textSize = m_colider.height / 2;
		m_textPosition = {
		m_colider.x + m_colider.width / 20,
		m_colider.y + m_colider.height / 4
		};
	}

	[[nodiscard]] EntryType GetValue() const {
		return m_value;
	};
	void SetValue(EntryType value, bool resize = false) {
		m_value = value;
		
		if (resize) {
			m_resizeCells();
		}
	};

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
		return m_colider;
	}
};


// needed size 
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
template<>
[[nodiscard]] inline Vector2 TableCell<Color>::GetNeededSize() {
	Vector2 neededSize = { 0.05f, 0.1f };
	return neededSize;
}

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