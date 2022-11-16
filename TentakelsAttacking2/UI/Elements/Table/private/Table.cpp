//
// Purpur Tentakel
// 01.10.2022
// 

#include "Table.h"
#include "Allignment.h"
#include "AppContext.h"
#include "PrimitiveCellPopUp.hpp"
#include "HGeneral.h"
#include "HFocusEvents.h"
#include "HInput.h"
#include <stdexcept>
#include <cassert>

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
void Table::CheckValidRowColumn(size_t row, size_t column) const {
	if (row < 0 or m_rows <= row) {
		throw std::out_of_range("row out of range: " + row);
	}
	if (column < 0 or m_columns <= column) {
		throw std::out_of_range("column out of range: " + column);
	}
}

void Table::SetElementFocus(Focusable* toFocus) const {
	if (!m_isNestedFocus) {
		return;
	}

	AddFocusElement(toFocus, m_isPopUp);
}
void Table::SelectElementFocus(Focusable* toFocus) const {
	SelectFocusElement(toFocus, m_isPopUp);
}
void Table::DeleteElementFocus(Focusable* toFocus) const {
	if (!m_isNestedFocus) {
		return;
	}

	DeleteFocusElement(toFocus, m_isPopUp);
}
void Table::SetFocusLayer() {
	if (m_isNestedFocus) {
		return;
	}

	AddFocusLayer(m_isPopUp);

	m_isNestedFocus = true;
}
void Table::DeleteFocusLayer() {
	if (!m_isNestedFocus) {
		return;
	}

	::DeleteFocusLayer(m_isPopUp);

	m_isNestedFocus = false;
}

std::vector<float> Table::GetColumnWidths() {
	std::vector<float> toReturn;

	for (int i = 0; i < m_columns; ++i) {
		toReturn.push_back(0.0f);
	}

	for (int row = 0; row < m_rows; ++row) {
		for (int column = 0; column < m_columns; ++column) {
			AbstractTableCell* currentCell = m_cells.at(
				GetIndexFromRowAndColumn(row, column, m_columns)).get();

			float cellWitdh = GetElementSizeReversed(
				m_size, currentCell->GetNeededSize()).x;

			
			if (toReturn.at(column) < cellWitdh) {
				toReturn.at(column) = cellWitdh;
			}
		}
	}

	return toReturn;
}
void Table::DistributeDeviationToColumns(
	std::vector<float>& neededWidths) {

	float deviation = 0.0f;
	for (float f : neededWidths) {
		deviation += f;
	}

	deviation = 1.0f - deviation;
	deviation /= neededWidths.size();

	for (size_t i = 0; i < neededWidths.size(); ++i) {
		neededWidths.at(i) += deviation;
	}
}
std::vector<float> Table::GetNewColumnPosition(
	std::vector<float> const& columnWidths) const {

	std::vector<float> positions;

	for (size_t column = 0; column < columnWidths.size(); ++column) {
		float position = 0.0f;
		for (size_t i = 0; i < column; ++i) {
			position += columnWidths.at(i);
		}
		positions.push_back(position);
	}

	return positions;
}

void Table::UpdateColider(Vector2 resolution) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
}

Table::Table(Vector2 pos, Vector2 size, Alignment alignment, unsigned int ID,
	size_t rows, size_t columns, Vector2 resolution, bool isPopUp)
	: UIElement(pos, size, alignment), Focusable(ID),
	m_rows(rows), m_columns(columns), m_resolution(resolution), m_isPopUp(isPopUp) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_cells.reserve(m_columns * m_rows);
	for (int row = 0; row < m_rows; ++row) {
		for (int column = 0; column < m_columns; ++column) {
			m_cells.push_back(std::make_unique<EmptyCell>(
				static_cast<unsigned int>(
					GetIndexFromRowAndColumn(row, column, m_columns)), // ID
				GetElementPosition(row, column),
				GetElementSize(),
				Alignment::DEFAULT,
				resolution
				));
		}
	}
}
Table::~Table() {
	DeleteFocusLayer();
}

void Table::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	bool updateCells = false;

	if (m_isNestedFocus) {
		updateCells = true;

		if (IsBackInputPressed()) {
			DeleteFocusLayer();
		}
	}


	if (!m_isNestedFocus) {
		if (!IsFocused()) {
			if (CheckCollisionPointRec(mousePosition, m_colider)) {
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					SelectElementFocus(this);

					updateCells = true;
				}
			}
		}

		if (IsFocused()) {
			bool mouseAction =
				CheckCollisionPointRec(mousePosition, m_colider)
				and IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
			bool enterAction = IsConfirmInputPressed() && !IsSkipInput();
			bool focusCell =
				enterAction
				or mouseAction;

			if (focusCell) {
				SetFocusLayer();

				for (auto& c : m_cells) {
					SetElementFocus(c.get());
				}

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
	m_cells.at(GetIndexFromRowAndColumn(row, column, m_columns))
		->SetEditable(editable);
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

size_t Table::GetRows() const {
	return m_rows;
}
size_t Table::GetColumns() const {
	return m_columns;
}

void Table::SetEmptyCell(size_t row, size_t column, bool resizeCells) {
	CheckValidRowColumn(row, column);
	size_t index = GetIndexFromRowAndColumn(row, column, m_columns);
	if (auto const* cell = dynamic_cast<EmptyCell const*>(m_cells.at(index).get())) {
		return;
	}

	DeleteElementFocus(m_cells.at(index).get());
	bool isEditable = m_cells.at(index)->IsEnabled();

	m_cells.at(index) = std::make_unique<EmptyCell>(
		static_cast<unsigned int>(
			GetIndexFromRowAndColumn(row, column, m_columns)), // ID
		GetElementPosition(row, column),
		GetElementSize(),
		Alignment::DEFAULT,
		m_resolution
		);

	m_cells.at(index)->SetEditable(isEditable);
	SetElementFocus(m_cells.at(index).get());

	if (resizeCells) {
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
		SetValue<std::string>(0, i, headlines.at(i), false);
	}

	if (resizeCells) {
		ResizeCells();
	}
}

void Table::ResizeCells() {
	std::vector<float> columnWidths = GetColumnWidths();
	DistributeDeviationToColumns(columnWidths);
	std::vector<float> positions = GetNewColumnPosition(columnWidths);

	assert(columnWidths.size() == positions.size());

	for (size_t i = 0; i < columnWidths.size(); ++i) {
		columnWidths.at(i) = ::GetElementSize(
			m_size, columnWidths.at(i), 0.0f
		).x;

		positions.at(i) = ::GetElementPosition(
			m_pos, m_size, positions.at(i), 0.0f
		).x;
	}

	AppContext& appContext = AppContext::GetInstance();

	for (size_t row = 0; row < m_rows; ++row) {
		for (size_t column = 0; column < m_columns; ++column) {
			AbstractTableCell* currentCell = m_cells.at(
				GetIndexFromRowAndColumn(row, column, m_columns)).get();
			currentCell->SetSizeX(
				columnWidths.at(column),
				m_resolution,
				appContext,
				false
			);
			currentCell->SetPosX(
				positions.at(column),
				m_resolution,
				appContext
			);
		}
	}
}
