//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include "AllCells.hpp"
#include "HGeneral.h"
#include "AppContext.h"
#include <memory>
#include <vector>

/**
 * provides a table with different cell types.
 */
class Table final : public UIElement, public Focusable {
private:
	bool m_isPopUp; ///< contains if the table was generated inside a popup

	std::vector<std::unique_ptr<AbstractTableCell>> m_cells; ///< contains all cells -> no cells are filled with empty cells
	size_t m_rows; ///< contains the amount of rows
	size_t m_columns; ///< contains the amount if columns
	/**
	 * contains the update llambdas for updating the cell values.
	 * needs the cell*, old value, new value.
	 */
	std::function<void(AbstractTableCell const*, std::string, std::string)> m_updatedStringCell = [](AbstractTableCell const*, std::string, std::string) {}; ///< string
	std::function<void(AbstractTableCell const*, int, int)> m_updatedIntCell = [](AbstractTableCell const*, int, int) {}; ///< int
	std::function<void(AbstractTableCell const*, float, float)> m_updatedFloatCell = [](AbstractTableCell const*, float, float) {}; ///< float
	std::function<void(AbstractTableCell const*, double, double)> m_updatedDoubleCell = [](AbstractTableCell const*, double, double) {}; ///< double
	std::function<void(AbstractTableCell const*, Color, Color)> m_updatedColorCell = [](AbstractTableCell const*, Color, Color) {}; ///< color

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

	/**
	 * returns the initial position of a cell.
	 */
	[[nodiscard]] Vector2 GetElementPosition(size_t row, size_t column) const;
	/**
	 * returns the initial size of a cell.
	 */	
	[[nodiscard]] Vector2 GetElementSize() const;
	/**
	 * checks if row and column are valid for this table.
	 * throws an exception if not.
	 */
	void CheckValidRowColumn(size_t row, size_t column) const;

	/**
	 * ealry return if not nested focus.
	 * adds the provided focusable.
	 */
	void SetElementFocus(Focusable* toFocus) const;
	/**
	 * selects the provided focusable.
	 */
	void SelectElementFocus(Focusable* toFocus) const;
	/**
	 * ealry return if not nested focus.
	 * deletes the provided focusable.
	 */
	void DeleteElementFocus(Focusable* toFocus) const;
	/**
	 * ealry return if nested focus.
	 * adds focus layer.
	 */
	void SetFocusLayer();
	/**
	 * ealry return if not nested focus.
	 * deletes focus layer.
	 */
	void DeleteFocusLayer();

	/**
	 * collects and returns all cell column width.
	 */
	[[nodiscard]] std::vector<float> GetColumnWidths();
	/**
	 * calculates the diviation so that the table is 1.0f in width.
	 * distrebutes the diviation to all columns.
	 */
	void DistributeDeviationToColumns(std::vector<float>& neededWidths);
	/**
	 * calculates and returs the new cell position out of the new column witdhs
	 */
	[[nodiscard]] std::vector<float> GetNewColumnPosition(std::vector<float> const& newColumnWidths) const;

	/**
	 * sets a non empty cell with no value.
	 * the cell that is at that index gets overwritten.
	 */
	template<typename T>
	void SetCell(size_t row, size_t column) {
		const size_t index = GetIndexFromRowAndColumn(row, column, m_columns);
		const bool isEditable = m_cells.at(index)->IsEnabled();
		DeleteElementFocus(m_cells.at(index).get());

		m_cells.at(index) = std::make_unique<TableCell<T>>(
			static_cast<unsigned int>(index),
			GetElementPosition(row, column),
			GetElementSize(),
			Alignment::DEFAULT,
			m_resolution,
			[this]() {this->ResizeCells();},
			[this](AbstractTableCell const* cell, T oldValue, T newValue)
			{this->CellUpdated<T>(cell, oldValue, newValue);}
			);

		m_cells.at(index)->SetEditable(isEditable);
		SetElementFocus(m_cells.at(index).get());
	}

public:
	/**
	 * ctor.
	 * initializes the table with empty cells.
	 */
	Table(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		size_t rows, size_t columns, bool isPopUp = false);
	/**
	 * deletes a focus layer.
	 */
	~Table();

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
	 * table logic.
	 * calls cells to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * render the table.
	 * calls cells to render.
	 */
	void Render(AppContext const& appContext) override;
	/**
	 * rezises the table.
	 * calls cells to sezise.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	/**
	 * sets for all cells if the cells are editable.
	 */
	void SetAllCellsEditable(bool editable);
	/**
	 * sets for a row if the cells are editable.
	 */
	void SetRowEditable(size_t row, bool editable);
	/**
	 * sets for a column if the cells are editable.
	 */
	void SetColumnEditable(size_t column, bool editable);
	/**
	 * sets for a single cell if the cell is editable.
	 */
	void SetSingleCellEditable(size_t row, size_t column, bool editable);
	/**
	 * returns if the table is editable.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * returns the current resolution.
	 */
	[[nodiscard]] Vector2 GetResolution() const;

	/**
	 * returns the row count of the table.
	 */
	[[nodiscard]] size_t GetRows() const;
	/**
	 * returns the column count of the table.
	 */
	[[nodiscard]] size_t GetColumns() const;

	/**
	 * sets an empty cell.
	 * overrides the current cell at that position.
	 */
	void SetEmptyCell(size_t row, size_t column, bool resizeCells = true);
	/**
	 * sets a value into a specific cell.
	 * if the cell type does not match the value type, a new cell is generated to match the value type.
	 */
	template<typename ValueType>
	void SetValue(size_t row, size_t column, ValueType value,
		bool resizeCells = true) {
		CheckValidRowColumn(row, column);
		size_t index = GetIndexFromRowAndColumn(row, column, m_columns);
		auto cell = dynamic_cast<TableCell<ValueType>*>(m_cells.at(index).get());
		if (!cell) {
			SetCell<ValueType>(row, column);
			cell = dynamic_cast<TableCell<ValueType>*>(m_cells.at(index).get());
		}

		cell->SetValue(value);

		if (resizeCells) {
			ResizeCells();
		}
	}
	/**
	 * sets strings in the first row as headlines.
	 * sets thees cells to non editable.
	 */
	void SetHeadlines(std::vector<std::string> const& headlines,
		bool resizeCells = true);
	/**
	 * calculates the new column witdh and sets the new cell positions and witdh.
	 */
	void ResizeCells();
};
