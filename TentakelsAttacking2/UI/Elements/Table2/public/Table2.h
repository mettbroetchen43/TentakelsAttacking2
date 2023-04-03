//
// Purpur Tentakel
// 03.04.2023
//

#include "UIElement.hpp"
#include "Focusable.h"

#pragma once

struct Cell {

};

class Table2 final : public UIElement, public Focusable {
private:
	int m_rowCount; ///< contains the current mount of rown in the table
	int m_columnCount; ///< contains the current mount of column in the table
	std::vector<Cell> m_cells; ///< contains all cells the table is holding
	Vector2 m_minCellSize; ///< contains the minimum relative size of one cell
	bool m_isScollable = false; ///< contains if it is able to scroll the table
	bool m_isFixedHeadline = false; ///< contains if the first row is fixed while scolling
	bool m_isFixedFirstColumn = false; ///< contains if the first column is fixed while scolling
	Vector2 m_scollOffset{ 0.0f,0.0f }; ///< contains the offset the cells have while scolling

	/**
	 * returns an index based on the provided row and column.
	 */
	[[nodiscard]] int GetIndex(int row, int column) const;
	/**
	 * returns true if the provided index is valid to access a cell.
	 */
	[[nodiscard]] bool IsValidIndex(int index) const;
	/**
	 * returns true if the provided row  is valid to access a cell.
	 */
	[[nodiscard]] bool IsValidRow(int row) const;
	/**
	 * returns true if the provided column is valid to access a cell.
	 */
	[[nodiscard]] bool IsValidColumn(int column) const;


public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	Table2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID, int rowCount, int columnCount, Vector2 minCellSize);


	/**
	 * replaces the current Cell with a new one.
	 */
	template<typename T>
	void SetCell(int row, int column, T input);
	/**
	 * Replaces the specific cell with an empty cell.
	 */
	void ClearCell(int row, int column);

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
	 * sets the new row and column count.
	 * resizes the table.
	 */
	void ResizeTable(int newRowCount, int newColumnCount);
	/**
	 * resizes the table.
	 */
	void ResizeTable();

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
	void SetAllEditable(bool IsEditable);
	/**
	 * returns true if all cells are editable.
	 * returns false if at least one cell is not editable.
	 */
	[[nodiscard]] bool IsAllEditable() const;

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
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the table.
	 * calls all cells to check and Update itself.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext const&) override;
	/**
	 * renders the table.
	 * calls all cells to render itself.
	 */
	void Render(AppContext const& appContext) override;
};

