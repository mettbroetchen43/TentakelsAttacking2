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

class Table : public UIElement, public Focusable {
private:
	std::vector<std::unique_ptr<AbstractTableCell>> m_cells;
	size_t m_rows;
	size_t m_columns;
	Rectangle m_colider;
	Vector2 m_resolution;
	std::function<void(AbstractTableCell const*, std::string, std::string)> m_updatedStringCell = [](AbstractTableCell const*, std::string, std::string) {};
	std::function<void(AbstractTableCell const*, int, int)> m_updatedIntCell = [](AbstractTableCell const*, int, int) {};
	std::function<void(AbstractTableCell const*, float, float)> m_updatedFloatCell = [](AbstractTableCell const*, float, float) {};
	std::function<void(AbstractTableCell const*, double, double)> m_updatedDoubleCell = [](AbstractTableCell const*, double, double) {};
	std::function<void(AbstractTableCell const*, Color, Color)> m_updatedColorCell = [](AbstractTableCell const*, Color, Color) {};

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

	[[nodiscard]] Vector2 GetElementPosition(size_t row, size_t column) const;
	[[nodiscard]] Vector2 GetElementSize() const;
	[[nodiscard]] void CheckValidRowColumn(size_t row, size_t column) const;

	[[nodiscard]] std::vector<float> GetColumnWidths();
	void DistributeDeviationToColumns(
		std::vector<float>& neededWidths);
	[[nodiscard]] std::vector<float> GetNewColumnPosition(
		std::vector<float> const& newColumnWidths) const;

	template<typename EntryType>
	void SetCell(size_t row, size_t column) {
		const size_t index = GetIndexFromRowAndColumn(row, column, m_columns);
		const bool isEditable = m_cells.at(index)->IsEnabled();
		m_cells.at(index) = std::make_unique<TableCell<EntryType>>(
			static_cast<unsigned int>(index),
			GetElementPosition(row, column),
			GetElementSize(),
			Alignment::DEFAULT,
			m_resolution,
			[&]() {ResizeCells();},
			[&](AbstractTableCell const* cell, EntryType oldValue, EntryType newValue)
			{CellUpdated<EntryType>(cell, oldValue, newValue);}
			);
		m_cells.at(index)->SetEditable(isEditable);
	}

public:
	Table(Vector2 pos, Vector2 size, Alignment alignment, unsigned int ID,
		size_t rows, size_t columns, Vector2 resolution);

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

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetAllCellsEditable(bool editable);
	void SetRowEditable(size_t row, bool editable);
	void SetColumnEditable(size_t column, bool editable);
	void SetSingleCellEditable(size_t row, size_t column, bool editable);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	[[nodiscard]] Vector2 GetResolution() const;

	[[nodiscard]] size_t GetRows() const;
	[[nodiscard]] size_t GetColumns() const;

	void SetEmptyCell(size_t row, size_t column, bool resizeCells = true);
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
	void SetHeadlines(std::vector<std::string> const& headlines,
		bool resizeCells = true);
	void ResizeCells();
};
