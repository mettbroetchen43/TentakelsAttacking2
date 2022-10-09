//
// Purpur Tentakel
// 01.10.2022
// 

#include "Table.h"
#include "Allignment.h"
#include "AppContext.h"
#include "StringCellPopUp.h"
#include <stdexcept>

size_t Table::GetIndex(size_t row, size_t column) const {
	return row * m_columns + column;
}
Vector2 Table::GetElementPosition(size_t row, size_t column) const {
	Vector2 elementSize = GetElementSize();
	return Vector2 { 
		m_pos.x + (elementSize.x * column),
		m_pos.y + (elementSize.y * row)
	};
}
Vector2 Table::GetElementSize() const {
	return Vector2{
		m_size.x / m_columns,
		m_size.y / m_rows
	};
}
[[nodiscard]] void Table::CheckValidRowColumn(size_t row, size_t column) const {
	if (row < 0 or m_rows <= row) {
		throw std::out_of_range("row out of range: " + row);
	}
	if (column < 0 or m_columns <= column) {
		throw std::out_of_range("column out of range: " + column);
	}
}

Table::Table(Vector2 pos, Vector2 size, Alignment alignment, unsigned int ID,
	size_t rows, size_t columns, Vector2 resolution)
	: UIElement(pos, size, alignment), Focusable(ID),
	m_rows(rows), m_columns(columns), m_resolution(resolution) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_cells.reserve(m_columns * m_rows);
	for (int row = 0; row < m_rows; ++row) {
		for (int column = 0; column < m_columns; ++column) {
			m_cells.push_back(std::make_unique<EmptyCell>(
				GetElementPosition(row, column),
				GetElementSize(),
				Alignment::DEFAULT,
				static_cast<unsigned int>(GetIndex(row, column)),
				resolution,
				this
				));
		}
	}
}

void Table::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	bool updateCells = false;

	if (m_cellFocus) {
		updateCells = true;

		if (IsKeyPressed(KEY_ESCAPE)) {
			auto event = DeleteFocusLayerEvent();
			appContext.eventManager.InvokeEvent(event);
			m_cellFocus = false;
		}
	}


	if (!m_cellFocus) {
		if (!IsFocused()) {
			if (CheckCollisionPointRec(mousePosition, m_colider)) {
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					auto event = SelectFocusElementEvent(this);
					appContext.eventManager.InvokeEvent(event);

					updateCells = true;
				}
			}
		}

		if (IsFocused()) {
			bool mouseAction =
				CheckCollisionPointRec(mousePosition, m_colider)
				and IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
			bool enterAction =
				IsKeyPressed(KEY_ENTER)
				or IsKeyPressed(KEY_SPACE);
			bool focusCell =
				enterAction
				or mouseAction;

			if (focusCell) {
				auto event = NewFocusLayerEvent();
				appContext.eventManager.InvokeEvent(event);
				for (auto& c : m_cells) {
					auto event2 = NewFocusElementEvent(c.get());
					appContext.eventManager.InvokeEvent(event2);
				}
				m_cellFocus = true;

				if (mouseAction) {
					updateCells = true;
				}
			}
		}
	}

	if (updateCells) {
		for (auto& c : m_cells) {
			c->CheckAndUpdate(mousePosition, appContext);
		}
	}
}
void Table::Render(AppContext const& appContext){
	for (auto& c : m_cells) {
		c->Render(appContext);
	}
}
void Table::Resize(Vector2 resolution, AppContext const& appContext){
	m_resolution = resolution;
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};

	for (auto& c : m_cells) {
		c->Resize(resolution, appContext);
	}
}

void Table::SetAllCellsEditable(bool editable) {
	for (auto& c : m_cells) {
		c->SetEditable(editable);
	}
}
void Table::SetRowEditable(size_t row, bool editable) {
	// index check in SetSingleColumnEditable
	for (int column = 0; column < m_columns; ++column) {
		SetSingleCellEditable(row, column, editable);
	}
}
void Table::SetColumnEditable(size_t column, bool editable) {
	// index check in SetSingleColumnEditable
	for (int row = 0; row < m_rows; ++row) {
		SetSingleCellEditable(row, column, editable);
	}
}
void Table::SetSingleCellEditable(size_t row, size_t column, bool editable) {
	CheckValidRowColumn(row, column);
	m_cells.at(GetIndex(row, column))->SetEditable(editable);
}
bool Table::IsEnabled() const {
	return true;
}
Rectangle Table::GetCollider() const {
	return m_colider;
}

Vector2 Table::GetResolution() const {
	return m_resolution;
}

void Table::SetEmptyCell(size_t row, size_t column, bool resizeCells) {
	CheckValidRowColumn(row, column);
	SetCell<EmptyCell>(row, column);

	if (resizeCells) {
		std::cout << "SET EMPTY CELL RESIZE\n";
		ResizeCells();
	}
}
void Table::SetHeadlines(std::vector<std::string> const& headlines,
	bool resizeCells) {
	if (headlines.size() != m_columns) {
		throw std::out_of_range(
			"headlines count does not match the column count"
		);
	}

	for (int i = 0; i < m_columns; ++i) {
		SetValue<StringCell, std::string>(0, i, headlines.at(i), false);
	}

	if (resizeCells) {
		std::cout << "SET HEADLINES RESIZE\n";
		ResizeCells();
	}
}

void Table::ResizeCells() {
	std::cout << "RESIZE CELLS NOW!\n";
}
