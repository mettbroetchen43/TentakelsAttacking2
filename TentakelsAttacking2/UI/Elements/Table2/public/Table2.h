//
// Purpur Tentakel
// 03.04.2023
//

#include "HPrint.h"
#include "Focusable.h"
#include "UIElement.hpp"
#include "HFocusEvents.h"
#include "TableCell2.hpp"
#include <memory>
#include <stdexcept>

#pragma once

class Table2 final : public UIElement, public Focusable {
private:
	using cells_ty = std::vector<std::vector<std::shared_ptr<AbstactTableCell2>>>;
	int m_rowCount; ///< contains the current mount of rown in the table
	int m_columnCount; ///< contains the current mount of column in the table
	cells_ty m_cells; ///< contains all cells the table is holding
	Vector2 m_minCellSize; ///< contains the minimum relative size of one cell
	std::array<std::vector<bool>, 2> m_editableRowsColumns; ///< contains the enabled rows and columns
	Rectangle m_temporaryCollider; ///< contains the used collider

	bool m_setScrollable = false; ///< contains if the table get set scrollable this frame
	bool m_isScrollable = false; ///< contains if it is able to scroll the table
	bool m_setFixedHeadline = false; ///< contains if the forst row will get fixed this frame
	bool m_isFixedHeadline = false; ///< contains if the first row is fixed while scolling
	bool m_setFixedFirstColumn = false; ///< contains if the first column will get wixed this frame
	bool m_isFixedFirstColumn = false; ///< contains if the first column is fixed while scolling
	float m_scroll_speed; ///< contains the speed the table ist scrolled with
	Vector2 m_absoluteScollingOffset{ 0.0f,0.0f }; ///< contains the absolute scrolling offset 

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
	void CheckAndUpdateClickCell(Vector2 const& mousePositon, AppContext const& appContext);

	/**
	 * checks and scrolls if scrollable
	 */
	void CheckAndUpdateScroll(Vector2 const& mousePosition);
	/**
	 * clamps the scroll offset so that the table can not "leave" the collider.
	 */
	void ClampScroollOffset(Vector2& offset);
	/**
	 * moves a selected cell in the table collider.
	 */
	void ScrollFocused();
	/**
	 * moves the cell collider of the offset.
	 */
	void ScrollMove(Vector2 const& offset);

	/**
	 * calls the top left cell to render.
	 * sets the scissors mode for it.
	 */
	void RenderTopLeft(AppContext const& appContext);
	/**
	 * calls the headline (without the top left corner) to render.
	 * sets the scissors mode for it.
	 */
	void RenderHeadline(AppContext const& appContext);
	/**
	 * calls the first column (without the top left corner) to render.
	 * sets the scissors mode for it.
	 */
	void RenderFirstColumn(AppContext const& appContext);
	/**
	 * calls all the other cells to render.
	 * sets the scissors mode for it.
	 */
	void RenderOtherCells(AppContext const& appContext);
	/**
	 * renders the outline of the table.
	 * sets the scissors mode for it.
	 */
	void RenderOutline() const;

public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	Table2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID,
		int rowCount, int columnCount, Vector2 minCellSize, float scrollSpeed);

	/**
	 * replaces the current Cell with a new one.
	 */
	template<typename T>
	void SetValue(int row, int column, T input) {
		if (not IsValidIndex(row, column)) { Print("Index out of range", PrintType::ERROR), throw std::out_of_range("index"); }

		auto oldCell = m_cells.at(row).at(column);
		if (IsNestedFocus()) {
			DeleteFocusElement(oldCell.get());
		}

		auto cell = std::make_shared<TableCell2<T>>(
			oldCell->GetPosition(),
			oldCell->GetSize(),
			oldCell->GetAlignment(),
			m_resolution,
			oldCell->GetFocusID(),
			input
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

		std::any value = m_cells.at(row).at(column)->GetValue();
		return std::any_cast<T>(value);
	}
	/**
	 * rerturn the current valeu of a cell as string.s
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
	void AddSpecificRow(int row, T defalutValue) {
		if (row == m_cells.size()) { /* nothing */ }
		else if (!IsValidRow(row)) { Print("invalid row index", PrintType::ERROR), throw std::out_of_range("row-index"); }

		auto line = std::vector<std::shared_ptr<AbstactTableCell2>>();

		for (int column = 0; column < m_columnCount; ++column) {

			auto cell = std::make_shared<TableCell2<T>>(
				Vector2(0.0f, 0.0f),
				Vector2(0.1f, 0.1f),
				Alignment::TOP_LEFT,
				m_resolution,
				0,
				defalutValue
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
	 * adds a specific colunm.
	 */
	template <typename T>
	void AddSpecificColumn(int column, T defalutValue) {
		if (m_cells.size() == 0) { Print("no rows available in the table", PrintType::ERROR), throw std::out_of_range("no rows"); }
		else if (column == m_cells.at(0).size()) { /* nothing */ }
		else if (!IsValidColumn(column)) { Print("column-index out of range", PrintType::ERROR), throw std::out_of_range("column index"); }

		for (int i = 0; i < m_rowCount; ++i) {
			auto row = m_cells.at(i);
			auto cell = std::make_shared<TableCell2<T>>(
				Vector2(0.0f, 0.0f),
				Vector2(0.1f, 0.1f),
				Alignment::TOP_LEFT,
				m_resolution,
				0,
				defalutValue
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
	void AddLastColumn(T defalutValue) {
		if (m_cells.size() == 0) { Print("no rows in table", PrintType::ERROR), throw std::out_of_range("no rows"); }
		AddSpecificColumn<T>(static_cast<int>(m_cells.at(0).size()), defalutValue);
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
	 * removes a specific colunm.
	 */
	void RemoveSpecificColumn(int column);
	/**
	 * removes the last column.
	 * calls RemoveSpecificColumn.
	 */
	void RemoveLastColum();

	/**
	 * Sets if the table is scollable.
	 */
	void SetScrollable(bool isScollable);
	/**
	 * returns true if the table is currently scollable.
	 */
	[[nodiscard]] bool IsScollable() const;

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
	 * sets if the first row is fixed while scolling.
	 */
	void SetFixedHeadline(bool isFixedHeadline);
	/**
	 * returns true if the first row is fixed while scolling.
	 */
	[[nodiscard]] bool IsFixedHeadline() const;

	/**
	 * sets if the first column is fixed while scolling.
	 */
	void SetFixedFirstColumn(bool isFixedFirstColumn);
	/**
	 * returns true if the first column is fixed while scolling.
	 */
	[[nodiscard]] bool IsFixedFirstColumn() const;

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
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the table.
	 * calls all cells to render itself.
	 */
	void Render(AppContext const& appContext) override;
};
