//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "UIElement.h"
#include "Focusable.h"
#include "AllCells.h"
#include <memory>
#include <vector>

class Table : public UIElement, public Focusable {
private:
	std::vector<std::unique_ptr<Cell>> m_cells;
	size_t m_rows;
	size_t m_columns;
	Rectangle m_colider;
	Vector2 m_resolution;

	[[nodiscard]] size_t GetIndex(size_t row, size_t column) const;
	[[nodiscard]] Vector2 GetElementPosition(size_t row, size_t column) const;
	[[nodiscard]] Vector2 GetElementSize() const;

	template<typename CellType>
	void SetCell(size_t row, size_t column) {
		const size_t index = GetIndex(row, column);
		m_cells[index] = std::make_unique<CellType>(
			GetElementPosition(row, column),
			GetElementSize(),
			Alignment::DEFAULT,
			static_cast<unsigned int>(index),
			m_resolution
			);
	}

protected:

public:
	Table(Vector2 pos, Vector2 size, Alignment alignment, unsigned int ID,
		size_t rows, size_t columns, Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void SetEmptyCell(size_t row, size_t column);

	template<typename CellType, typename ValueType>
	void SetValue(size_t row, size_t column, ValueType value) {
		size_t index = GetIndex(row, column);
		auto cell = dynamic_cast<CellType*>(m_cells.at(index).get());
		if (!cell) {
			SetCell<CellType>(row, column);
			cell = dynamic_cast<CellType*>(m_cells.at(index).get());
		}

		cell->value = value;
	}
};
