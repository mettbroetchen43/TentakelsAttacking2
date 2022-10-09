//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include "AllCells.hpp"
#include "HGeneral.h"
#include <memory>
#include <vector>
#include <iostream>

class Table : public UIElement, public Focusable {
private:
	std::vector<std::unique_ptr<Cell>> m_cells;
	size_t m_rows;
	size_t m_columns;
	Rectangle m_colider;
	Vector2 m_resolution;
	bool m_cellFocus = false;

	[[nodiscard]] Vector2 GetElementPosition(size_t row, size_t column) const;
	[[nodiscard]] Vector2 GetElementSize() const;
	[[nodiscard]] void CheckValidRowColumn(size_t row, size_t column) const;

	[[nodiscard]] std::vector<float> GetColumnWidths() const;

	template<typename CellType>
	void SetCell(size_t row, size_t column) {
		const size_t index = GetIndexFromRowAndColumn(row, column, m_columns);
		const bool isEditable = m_cells.at(index)->IsEnabled();
		m_cells.at(index) = std::make_unique<CellType>(
			GetElementPosition(row, column),
			GetElementSize(),
			Alignment::DEFAULT,
			static_cast<unsigned int>(index),
			m_resolution,
			this
			);
		m_cells.at(index)->SetEditable(isEditable);
	}

public:
	Table(Vector2 pos, Vector2 size, Alignment alignment, unsigned int ID,
		size_t rows, size_t columns, Vector2 resolution);

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

	void SetEmptyCell(size_t row, size_t column, bool resizeCells = true);
	template<typename CellType, typename ValueType>
	void SetValue(size_t row, size_t column, ValueType value,
		bool resizeCells = true) {
		CheckValidRowColumn(row, column);
		size_t index = GetIndexFromRowAndColumn(row, column, m_columns);
		auto cell = dynamic_cast<CellType*>(m_cells.at(index).get());
		if (!cell) {
			SetCell<CellType>(row, column);
			cell = dynamic_cast<CellType*>(m_cells.at(index).get());
		}

		cell->value = value;

		if (resizeCells) {
			ResizeCells();
		}
	}
	void SetHeadlines(std::vector<std::string> const& headlines,
		bool resizeCells = true);
	void ResizeCells();
};
