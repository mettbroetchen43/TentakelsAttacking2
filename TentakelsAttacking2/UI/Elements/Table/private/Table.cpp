//
// Purpur Tentakel
// 01.10.2022
// 

#include "Table.h"
#include "Allignment.h"

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
				resolution
				));
		}
	}
}

void Table::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (IsFocused()) {
		if (IsKeyPressed(KEY_ENTER)
			or IsKeyPressed(KEY_SPACE)) {
			// invoke focus event
			return;
		}
	}

	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			// invoke focus event
			return;
		}
	}

	for (auto& c : m_cells) {
		c->CheckAndUpdate(mousePosition, appContext);
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

bool Table::IsEnabled() const {
	return true;
}
Rectangle Table::GetCollider() const {
	return m_colider;
}

void Table::SetEmptyCell(size_t row, size_t column) {
	SetCell<EmptyCell>(row, column);
}
