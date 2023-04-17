//
// Purpur Tentakel
// 03.04.2023
//

#include "Table2.h"
#include "HPrint.h"
#include "HInput.h"
#include "HFocusEvents.h"
#include <stdexcept>


bool Table2::IsValidIndex(int row, int column) const {
	return
		IsValidRow(row)
		&& IsValidColumn(column);
}
bool Table2::IsValidRow(int row) const {
	return
		row < m_cells.size()
		&& row >= 0;
}
bool Table2::IsValidColumn(int column) const {
	if (m_cells.size() < 1) { return false; }
	return
		column < m_cells.at(0).size()
		&& column >= 0;
}

void Table2::UpdateCellFocusID() {
	for (int row = 0; row < m_cells.size(); ++row) {
		for (int column = 0; column < m_cells.at(row).size(); ++column) {
			m_cells.at(row).at(column)->SetFocusID(static_cast<unsigned int>(row * m_cells.size() + column));
		}
	}
}
void Table2::UpdateCellPositionAndSize() {
	if (m_isScollable) { Print("no imlementation for scrollable yet", PrintType::DEBUG); }
	else {
		float cellWidth = m_size.x / m_columnCount;
		float cellHeight = m_size.y / m_rowCount;

		for (int row = 0; row < m_cells.size(); ++row) {
			for (int column = 0; column < m_cells.at(row).size(); ++column) {
				auto& cell = m_cells.at(row).at(column);
				cell->SetPosition({ m_pos.x + cellWidth * column, m_pos.y + cellHeight * row });
				cell->SetSize({ cellHeight, cellWidth });
			}
		}
	}
}

void Table2::SetCellFocus() {
	SetNestedFocus(true);

	AddFocusLayer();
	for (auto const& line : m_cells) {
		for (auto const& cell : line) {
			AddFocusElement(cell.get());
		}
	}
}
void Table2::RemoveCellFocus() {
	DeleteFocusLayer();
	SetNestedFocus(false);
}

Table2::Table2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID,
	int rowCount, int columnCount, Vector2 minCellSize)
	: UIElement(pos, size, alignment, resolution), Focusable(focusID),
	m_rowCount(rowCount), m_columnCount(columnCount), m_minCellSize(minCellSize) {

	float cellWith = m_size.x / m_columnCount;
	float cellHeight = m_size.y / m_rowCount;

	m_cells.clear();
	for (int row = 0; row < m_rowCount; ++row) {

		auto line = std::vector<std::shared_ptr<AbstactTableCell2>>();
		for (int column = 0; column < columnCount; ++column) {

			auto cell = std::make_shared<AbstactTableCell2>(
				Vector2(m_pos.x + cellWith * column, m_pos.y + cellHeight * row),
				Vector2(cellWith, cellHeight),
				Alignment::TOP_LEFT,
				m_resolution,
				row * columnCount + column
			);

			line.push_back(cell);
		}
		m_cells.push_back(line);
	}

}

void Table2::SetRowCount(int newRowCount) {
	if (newRowCount <= 0) { Print("tryed to set a row count inside of a table that is lower than or equal to 0.", PrintType::ERROR); return; }

	m_rowCount = newRowCount;
}
int Table2::GetRowCount() const {
	return m_rowCount;
}

void Table2::SetColumnCount(int newColumnCount) {
	if (newColumnCount <= 0) { Print("tryed to set a column count inside of a table that is lower than or equal to 0.", PrintType::ERROR); return; }

	m_columnCount = newColumnCount;
}
int Table2::GetColumnCount() const {
	return m_columnCount;
}

void Table2::AddSpecificRow(int row) {
	if (row == m_cells.size()) { /* nothing */ }
	else if (!IsValidRow(row)) { Print("invalid row index", PrintType::ERROR), throw std::out_of_range("row-index"); }

	auto line = std::vector<std::shared_ptr<AbstactTableCell2>>();

	for (int column = 0; column < m_columnCount; ++column) {

		auto cell = std::make_shared<AbstactTableCell2>(
			Vector2(0.0f, 0.0f),
			Vector2(0.1f, 0.1f),
			Alignment::TOP_LEFT,
			m_resolution,
			0
		);
		line.push_back(cell);
	}

	m_cells.insert(m_cells.begin() + row, line);
}
void Table2::AddLastRow() {
	AddSpecificRow(static_cast<int>(m_cells.size()));
}
void Table2::AddSpecificColumn(int column) {
	if (m_cells.size() == 0) { Print("no rows available in the table", PrintType::ERROR), throw std::out_of_range("no rows"); }
	else if (column == m_cells.at(0).size()) { /* nothing */ }
	else if (!IsValidColumn(column)) { Print("column-index out of range", PrintType::ERROR), throw std::out_of_range("column index"); }

	for (auto& row : m_cells) {
		auto cell = std::make_shared<AbstactTableCell2>(
			Vector2(0.0f, 0.0f),
			Vector2(0.1f, 0.1f),
			Alignment::TOP_LEFT,
			m_resolution,
			0
		);
		row.insert(row.begin() + column, cell);
	}
}
void Table2::AddLastColumn() {
	if (m_cells.size() == 0) { Print("no rows in table", PrintType::ERROR), throw std::out_of_range("no rows"); }
	AddSpecificRow(static_cast<int>(m_cells.at(0).size()));
}

void Table2::RemoveSpecificRow(int row) {
	if (!IsValidRow(row)) { Print("row out of range", PrintType::ERROR), throw std::out_of_range("row index"); }

	m_cells.erase(m_cells.begin() + row);
}
void Table2::RemoveLastRow() {
	RemoveSpecificRow(static_cast<int>(m_cells.size() - 1));
}
void Table2::RemoveSpecificColumn(int column) {
	if (!IsValidColumn(column)) { Print("column index out of range", PrintType::ERROR), throw std::out_of_range("column index"); }

	for (auto& row : m_cells) {
		row.erase(row.begin() + column);
	}
}
void Table2::RemoveLastColum() {
	if (m_cells.size() == 0) { Print("no rows in table", PrintType::ERROR), throw std::out_of_range("no rows"); }
	RemoveSpecificColumn(static_cast<int>(m_cells.at(0).size() - 1));
}

void Table2::ResizeTable(int newRowCount, int newColumnCount) {
	SetRowCount(newRowCount);
	SetColumnCount(newColumnCount);

	ResizeTable();
}
void Table2::ResizeTable() {
	// rows
	if (m_cells.size() == m_rowCount) { /* nothing */ }
	else if (m_cells.size() < m_rowCount) {
		while (m_cells.size() < m_rowCount) {
			AddLastRow();
		}
	}
	else if (m_cells.size() > m_rowCount) {
		while (m_cells.size() > m_rowCount) {
			RemoveLastRow();
		}
	}

	if (m_cells.size() == 0) { Print("no rows in table", PrintType::ERROR), throw std::out_of_range("no rows"); }

	// columns
	auto& row = m_cells.at(0);
	if (row.size() == m_columnCount) { /* nothing */ }
	else if (row.size() < m_columnCount) {
		while (row.size() < m_columnCount) {
			AddLastColumn();
		}
	}
	else if (row.size() > m_columnCount) {
		while (row.size() > m_columnCount) {
			RemoveLastColum();
		}
	}

	UpdateCellFocusID();
	UpdateCellPositionAndSize();
}

void Table2::SetScrollable(bool isScollable) {
	m_isScollable = isScollable;
}
bool Table2::IsScollable() const {
	return m_isScollable;
}

void Table2::SetSingleEditable(int row, int column, bool isEditable) {
	if (!IsValidIndex(row, column)) { Print("row or column index out auf range", PrintType::ERROR); throw std::out_of_range("invalid index"); }

	m_cells.at(row).at(column)->SetEditable(isEditable);
}
bool Table2::IsSingleEditable(int row, int column) const {
	if (!IsValidIndex(row, column)) { Print("row or column index out auf range", PrintType::ERROR); throw std::out_of_range("invalid index"); }
	return m_cells.at(row).at(column)->IsEditable();
}

void Table2::SetAllEditable(bool IsEditable) noexcept {
	for (auto& row : m_cells) {
		for (auto& cell : row) {
			cell->SetEditable(IsEditable);
		}
	}
}
bool Table2::IsAllEditable() const noexcept {
	for (auto& row : m_cells) {
		for (auto& cell : row) {
			if (!cell->IsEditable()) { return false; }
		}
	}

	return true;
}

void Table2::SetRowEditable(int row, bool isEditable) {
	if (!IsValidRow(row)) { Print("row out of range", PrintType::ERROR), throw std::out_of_range("row index"); }

	for (auto& cell : m_cells.at(row)) {
		cell->SetEditable(isEditable);
	}
}
bool Table2::IsRowEditable(int row) const {
	if (!IsValidRow(row)) { Print("row out of range", PrintType::ERROR), throw std::out_of_range("row index"); }

	for (auto& cell : m_cells.at(row)) {
		if (!cell->IsEditable()) { return false; }
	}
	return true;
}

void Table2::SetColumnEditable(int column, bool isEditable) {
	if (!IsValidColumn(column)) { Print("column out of Range", PrintType::ERROR); throw std::out_of_range("column index"); }

	for (auto& row : m_cells) {
		row.at(column)->SetEditable(isEditable);
	}
}
bool Table2::IsColumnEditable(int column) const {
	if (!IsValidColumn(column)) { Print("column out of Range", PrintType::ERROR); throw std::out_of_range("column index"); }

	for (auto& row : m_cells) {
		if (row.at(column)->IsEditable()) { return false; }
	}
	return true;
}

void Table2::SetFixedHeadline(bool isFixedHeadline) {
	m_isFixedHeadline = isFixedHeadline;
}
bool Table2::IsFixedHeadline() const {
	return m_isFixedHeadline;
}

void Table2::SetFixedFirstColumn(bool isFixedFirstColumn) {
	m_isFixedFirstColumn = isFixedFirstColumn;
}
bool Table2::IsFixedFirstColumn() const {
	return m_isFixedFirstColumn;
}

bool Table2::IsEnabled() const noexcept {
	return true;
}
Rectangle Table2::GetCollider() const noexcept {
	return m_collider;
}

void Table2::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	for (auto const& row : m_cells) {
		for (auto const& cell : row) {
			cell->CheckAndUpdate(mousePosition, appContext);
		}
	}

	if (IsNestedFocus()) {
		if (IsBackInputPressed()) {
			RemoveCellFocus();
		}
	}

	else if (IsFocused()) {
		if (IsConfirmInputPressed()) {
			SetCellFocus();
		}
	}


}
void Table2::Render(AppContext const& appContext) {
	BeginScissorMode(
		static_cast<int>(m_collider.x),
		static_cast<int>(m_collider.y),
		static_cast<int>(m_collider.width),
		static_cast<int>(m_collider.height)
	);

	for (auto const& row : m_cells) {
		for (auto const& cell : row) {
			cell->Render(appContext);
		}
	}

	EndScissorMode();

	DrawRectangleLinesEx(m_collider, 2.0f, WHITE);
}
