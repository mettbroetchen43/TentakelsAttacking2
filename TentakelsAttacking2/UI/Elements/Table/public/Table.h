//
// Purpur Tentakel
// 03.04.2023
//

#include "HPrint.h"
#include "Focusable.h"
#include "UIElement.hpp"
#include "HFocusEvents.h"
#include "TableCell.hpp"
#include "Vec2.hpp"

#include <memory>
#include <stdexcept>

#pragma once

class Slider;

class Table final : public UIElement, public Focusable {
private:
	using cells_ty = std::vector<std::vector<std::shared_ptr<AbstractTableCell>>>;
	int m_rowCount; ///< contains the current mount of rows in the table
	int m_columnCount; ///< contains the current mount of column in the table
	cells_ty m_cells; ///< contains all cells the table is holding
	Vector2 m_minCellSize; ///< contains the minimum relative size of one cell
	std::array<std::vector<bool>, 2> m_editableRowsColumns; ///< contains the enabled rows and columns

	bool m_setScrollable{ false }; ///< contains if the table get set scrollable this frame
	bool m_isScrollable{ false }; ///< contains if it is able to scroll the table
	bool m_setFixedHeadline{ false }; ///< contains if the first row will get fixed this frame
	bool m_isFixedHeadline{ false }; ///< contains if the first row is fixed while scrolling
	bool m_setFixedFirstColumn{ false }; ///< contains if the first column will get fixed this frame
	bool m_isFixedFirstColumn{ false }; ///< contains if the first column is fixed while scrolling
	float m_scroll_speed; ///< contains the speed the table ist scrolled with
	Vector2 m_absoluteScrollingOffset{ 0.0f,0.0f }; ///< contains the absolute scrolling offset 

	Slider_ty m_horizontalSlider; ///< contains the horizontal slider
	bool m_activeHorizontalSlider; ///< contains if the horizontal slider is needed
	Slider_ty m_verticalSlider; ///< contains the vertical slider
	bool m_activeVerticalSlider; ///< contains if the vertical slider is needed

	bool m_isHoveredHighlighted{ false }; ///< contains if the hovered row and column gets highlighted
	vec2pos_ty m_currentHighlighted{ -1,-1 }; ///< contains the currently hightlithed row (x) and column (y) index

	std::function<void(AbstractTableCell const*, std::string, std::string)> m_updatedStringCell{ [](AbstractTableCell const*, std::string, std::string) {} }; ///< string
	std::function<void(AbstractTableCell const*, int, int)> m_updatedIntCell{ [](AbstractTableCell const*, int, int) {} }; ///< int
	std::function<void(AbstractTableCell const*, float, float)> m_updatedFloatCell{ [](AbstractTableCell const*, float, float) {} }; ///< float
	std::function<void(AbstractTableCell const*, double, double)> m_updatedDoubleCell{ [](AbstractTableCell const*, double, double) {} }; ///< double
	std::function<void(AbstractTableCell const*, Color, Color)> m_updatedColorCell{ [](AbstractTableCell const*, Color, Color) {} }; ///< color

	/**
	 * returns true if the provided index is valid to access a cell.
	 */
	[[nodiscard]] bool IsValidIndex(int row, int column) const;
	/**
	 * returns true if the provided row  is valid to access a cell.
	 */
	[[nodiscard]] bool IsValidRow(int row) const;
	/**
	 * returns true if the provided column is valid to access a cell.
	 */
	[[nodiscard]] bool IsValidColumn(int column) const;

	/**
	 * sets a new focus id in all cells.
	 */
	void UpdateCellFocusID();
	/**
	 * sets new size in all cells.
	 */
	void UpdateCellPositionAndSize();

	/**
	 * returns the calculated absolute size of all cells.
	 */
	[[nodiscard]] Vector2 GetAbsoluteSize() const;

	/**
	 * sets the cell focus and the nested focus.
	 */
	void SetCellFocus();
	/**
	 * removes the focus from the cells and the nested focus.
	 */
	void RemoveCellFocus();

	/**
	 * resizes the table.
	 */
	void ResizeTable();
	/**
	 * updates the headline position to fix it or not.
	 */
	void UpdateHeadlinePosition();
	/**
	 * updates the first row position to fix it or not.
	 */
	void UpdateFirstRowPosition();
	/**
	 * checks if any cell is clicked and updates it if so.
	 * returns after the top cell is clicked.
	 */
	void CheckAndUpdateClickCell(Vector2 const& mousePositon, AppContext_ty_c appContext);

	/**
	 * checks and scrolls if scrollable
	 */
	void CheckAndUpdateScroll(Vector2 const& mousePosition);
	/**
	 * clamps the scroll offset so that the table can not "leave" the collider.
	 */
	void ClampScrollOffset(Vector2& offset);
	/**
	 * moves a selected cell in the table collider.
	 */
	void ScrollFocused();
	/**
	 * set offset to position in percent.
	 */
	void ScrollPercent(float percent, bool isHorisonzal);
	/**
	 * moves the cell collider of the offset.
	 */
	void ScrollMove(Vector2 const& offset);
	/**
	 * sets the slider active or inactive and the total dimension.
	 */
	void CalculateSlider();

	/**
	 * calculates the current hovered row and column.
	 */
	void CalculateHoverHighlighted(Vector2 mousePosition);
	/**
	 * sets the background color of the highlighted cells.
	 * resets the background color if the bool is set.
	 * sets a new one if the bool is not set.
	 */
	void SetHighlightBackground(bool reset);

	/**
	 * calls the top left cell to render.
	 * sets the scissors mode for it.
	 */
	void RenderTopLeft(AppContext_ty_c appContext);
	/**
	 * calls the headline (without the top left corner) to render.
	 * sets the scissors mode for it.
	 */
	void RenderHeadline(AppContext_ty_c appContext);
	/**
	 * calls the first column (without the top left corner) to render.
	 * sets the scissors mode for it.
	 */
	void RenderFirstColumn(AppContext_ty_c appContext);
	/**
	 * calls all the other cells to render.
	 * sets the scissors mode for it.
	 */
	void RenderOtherCells(AppContext_ty_c appContext);
	/**
	 * renders the outline of the table.
	 * sets the scissors mode for it.
	 */
	void RenderOutline() const;


	/**
 * calls the valid lambda for the provided datatype.
 * update the cell that is provided by the pointer.
 */
	template<typename T>
	void CellUpdated(AbstractTableCell const* cell, T oldValue, T newValue) {
		if constexpr (std::is_same_v<T, std::string>) {
			m_updatedStringCell(cell, oldValue, newValue);
			return;
		}
		if constexpr (std::is_same_v<T, int>) {
			m_updatedIntCell(cell, oldValue, newValue);
			return;
		}
		if constexpr (std::is_same_v<T, float>) {
			m_updatedFloatCell(cell, oldValue, newValue);
			return;
		}
		if constexpr (std::is_same_v<T, double>) {
			m_updatedDoubleCell(cell, oldValue, newValue);
			return;
		}
		if constexpr (std::is_same_v<T, Color>) {
			m_updatedColorCell(cell, oldValue, newValue);
			return;
		}
	}

public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	Table(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID,
		int rowCount, int columnCount, Vector2 minCellSize, float scrollSpeed);

	/**
	 * replaces the current Cell with a new one.
	 */
	template<typename T>
	void SetValue(int row, int column, T input) {
		if (not IsValidIndex(row, column)) { Print("Index out of range", PrintType::ERROR), throw std::out_of_range("index"); }

		auto const oldCell{ m_cells.at(row).at(column) };
		if (IsNestedFocus()) {
			DeleteFocusElement(oldCell.get());
		}

		auto cell = std::make_shared<TableCell<T>>(
			oldCell->GetPosition(),
			oldCell->GetSize(),
			oldCell->GetAlignment(),
			m_resolution,
			oldCell->GetFocusID(),
			input,
			[this](AbstractTableCell const* cell, T oldValue, T newValue)
			{this->CellUpdated<T>(cell, oldValue, newValue); }
		);
		cell->SetEditable(oldCell->IsEditable());
		m_cells.at(row).at(column) = cell;
		if (IsNestedFocus()) {
			AddFocusElement(cell.get());
		}
	}
	/**
	 * returns the current value of a cell.
	 */
	template <typename T>
	[[nodiscard]] T GetValue(int row, int column) const {
		if (not IsValidIndex(row, column)) { Print("index out of range", PrintType::ERROR); throw std::out_of_range("index"); }

		std::any const value{ m_cells.at(row).at(column)->GetValue() };
		return std::any_cast<T>(value);
	}
	/**
	 * return the current value of a cell as string.
	 */
	[[nodiscard]] std::string GetValueAsString(int row, int column) const {
		if (not IsValidIndex(row, column)) { Print("index out of range", PrintType::ERROR); throw std::out_of_range("index"); }

		return m_cells.at(row).at(column)->GetValueAsString();
	}
	/**
	 * sets a new row count.
	 * need to call the recalculation of the table.
	 */
	void SetRowCount(int newRowCount);
	/**
	 * returns the current row count.
	 */
	[[nodiscard]] int GetRowCount() const;

	/**
	 * sets the update cell lambdas for the correct datatype.
	 */
	template<typename T>
	void SetUpdateSpecificCell(std::function<void(
		AbstractTableCell const*, T, T)> updateCell) {
		if constexpr (std::is_same_v<T, std::string>) {
			m_updatedStringCell = updateCell;
			return;
		}
		if constexpr (std::is_same_v<T, int>) {
			m_updatedIntCell = updateCell;
			return;
		}
		if constexpr (std::is_same_v<T, float>) {
			m_updatedFloatCell = updateCell;
			return;
		}
		if constexpr (std::is_same_v<T, double>) {
			m_updatedDoubleCell = updateCell;
			return;
		}
		if constexpr (std::is_same_v<T, Color>) {
			m_updatedColorCell = updateCell;
			return;
		}
	}


	/**
	 * sets a new column count.
	 * need to call the recalculation of the table.
	 */
	void SetColumnCount(int newColumnCount);
	/**
	 * returns the current column count.
	 */
	[[nodiscard]] int GetColumnCount() const;

	/**
	 * adds a specific row.
	 */
	template <typename T>
	void AddSpecificRow(int row, T defaultValue) {
		if (row == m_cells.size()) { /* nothing */ }
		else if (!IsValidRow(row)) { Print("invalid row index", PrintType::ERROR), throw std::out_of_range("row-index"); }

		auto line{ std::vector<std::shared_ptr<AbstractTableCell>>() };

		for (int column = 0; column < m_columnCount; ++column) {

			auto cell = std::make_shared<TableCell<T>>(
				Vector2(0.0f, 0.0f),
				Vector2(0.1f, 0.1f),
				Alignment::TOP_LEFT,
				m_resolution,
				0,
				defaultValue,
				[this](AbstractTableCell const* cell, T oldValue, T newValue)
				{this->CellUpdated<T>(cell, oldValue, newValue); }
			);
			if (not m_editableRowsColumns.at(1).at(column)) {
				cell->SetEditable(false);
			}
			line.push_back(cell);
		}

		m_cells.insert(m_cells.begin() + row, line);
		m_editableRowsColumns.at(0).insert(m_editableRowsColumns.at(0).begin() + row, true);
		++m_rowCount;
	}
	/**
	 * adds the last row.
	 * calls AddSpecificRow.
	 */
	template <typename T>
	void AddLastRow(T defalutValue) {
		AddSpecificRow<T>(static_cast<int>(m_cells.size()), defalutValue);
	}
	/**
	 * adds a specific column.
	 */
	template <typename T>
	void AddSpecificColumn(int column, T defalutValue) {
		if (m_cells.size() == 0) { Print("no rows available in the table", PrintType::ERROR), throw std::out_of_range("no rows"); }
		else if (column == m_cells.at(0).size()) { /* nothing */ }
		else if (!IsValidColumn(column)) { Print("column-index out of range", PrintType::ERROR), throw std::out_of_range("column index"); }

		for (int i = 0; i < m_rowCount; ++i) {
			auto row = m_cells.at(i);
			auto cell = std::make_shared<TableCell<T>>(
				Vector2(0.0f, 0.0f),
				Vector2(0.1f, 0.1f),
				Alignment::TOP_LEFT,
				m_resolution,
				0,
				defalutValue,
				[this](AbstractTableCell const* cell, T oldValue, T newValue)
				{this->CellUpdated<T>(cell, oldValue, newValue); }
			);
			if (not m_editableRowsColumns.at(0).at(i)) {
				cell->SetEditable(false);
			}
			row.insert(row.begin() + column, cell);
		}
		m_editableRowsColumns.at(1).insert(m_editableRowsColumns.at(1).begin() + column, true);
		++m_columnCount;
	}
	/**
	 * adds the last column.
	 * calls AddSpecificColumn.
	 */
	template <typename T>
	void AddLastColumn(T defaultValue) {
		if (m_cells.size() == 0) { Print("no rows in table", PrintType::ERROR), throw std::out_of_range("no rows"); }
		AddSpecificColumn<T>(static_cast<int>(m_cells.at(0).size()), defaultValue);
	}

	/**
	 * removes a specific row.
	 */
	void RemoveSpecificRow(int row);
	/**
	 * removes the last row.
	 * calls RemoveSpecificRow.
	 */
	void RemoveLastRow();
	/**
	 * removes a specific column.
	 */
	void RemoveSpecificColumn(int column);
	/**
	 * removes the last column.
	 * calls RemoveSpecificColumn.
	 */
	void RemoveLastColum();

	/**
	 * sets if the hovered row and column gets highlighted.
	 */
	void SetHighlightHover(bool isHoveredHighlighted);
	/**
	 * returns if the hovered row and column gets currently highlighted.
	 */
	[[nodiscard]] bool IsHighlightedHover() const;

	/**
	 * Sets if the table is scrollable.
	 */
	void SetScrollable(bool isScollable);
	/**
	 * returns true if the table is currently scrollable.
	 */
	[[nodiscard]] bool IsScrollable() const;

	/**
	 * sets if a specific cell is editable.
	 */
	void SetSingleEditable(int row, int column, bool isEditable);
	/**
	 * returns true if a specific cell is editable.
	 */
	[[nodiscard]] bool IsSingleEditable(int row, int column) const;

	/**
	 * Set if all cells are editable.
	 */
	void SetAllEditable(bool IsEditable) noexcept;
	/**
	 * returns true if all cells are editable.
	 * returns false if at least one cell is not editable.
	 */
	[[nodiscard]] bool IsAllEditable() const noexcept;

	/**
	 * sets if all cells in a specific row are editable.
	 */
	void SetRowEditable(int row, bool isEditable);
	/**
	 * returns true if all cells in a specific row are editable.
	 * returns false if at least one cell in a specific row is not editable.
	 */
	[[nodiscard]] bool IsRowEditable(int row) const;

	/**
	 * sets if all cells in a specific column are editable.
	 */
	void SetColumnEditable(int column, bool isEditable);
	/**
	 * returns true if all cells in a specific column are editable.
	 * returns false if at least one cell in a specific column is not editable.
	 */
	[[nodiscard]] bool IsColumnEditable(int column) const;

	/**
	 * sets if the first row is fixed while scrolling.
	 */
	void SetFixedHeadline(bool isFixedHeadline);
	/**
	 * returns true if the first row is fixed while scrolling.
	 */
	[[nodiscard]] bool IsFixedHeadline() const;

	/**
	 * sets if the first column is fixed while scrolling.
	 */
	void SetFixedFirstColumn(bool isFixedFirstColumn);
	/**
	 * returns true if the first column is fixed while scrolling.
	 */
	[[nodiscard]] bool IsFixedFirstColumn() const;
	/**
	 * sets the headline values.
	 */
	template<typename T>
	void SetHeadlineValues(std::vector<T> values) {
		for (int i = 0; i < m_columnCount; ++i) {
			if (i >= values.size()) {
				break;
			}
			SetValue<T>(0, i, values.at(i));
		}
	}

	/**
	 * returns if the current elements is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const noexcept override;
	/**
	 * returns thr current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const noexcept override;

	/**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the table.
	 * calls all cells to check and Update itself.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the table.
	 * calls all cells to render itself.
	 */
	void Render(AppContext_ty_c appContext) override;
};
