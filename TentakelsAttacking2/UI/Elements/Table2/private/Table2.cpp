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
			m_cells.at(row).at(column)->SetFocusID(static_cast<unsigned int>(row * m_columnCount + column));
		}
	}
}
void Table2::UpdateCellPositionAndSize() {

	float cellWidth;
	float cellHeight;

	if (m_isScollable) {

		Vector2 tableSize{
			m_minCellSize.x * m_columnCount,
			m_minCellSize.y * m_rowCount
		};

		auto cellSize = m_minCellSize;

		if (tableSize.x < m_size.x) {
			cellSize.x += (m_size.x - tableSize.x) / m_columnCount;
		}

		cellWidth = cellSize.x;
		cellHeight = cellSize.y;
	}
	else {
		cellWidth = m_size.x / m_columnCount;
		cellHeight = m_size.y / m_rowCount;
	}

	for (int row = 0; row < m_cells.size(); ++row) {
		for (int column = 0; column < m_cells.at(row).size(); ++column) {
			auto& cell = m_cells.at(row).at(column);
			cell->SetPosition({ m_pos.x + cellWidth * column, m_pos.y + cellHeight * row });
			cell->SetSize({ cellWidth, cellHeight });
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

	float cellWidth = m_size.x / m_columnCount;
	float cellHeight = m_size.y / m_rowCount;

	m_cells.clear();
	for (int row = 0; row < m_rowCount; ++row) {

		auto line = std::vector<std::shared_ptr<AbstactTableCell2>>();
		for (int column = 0; column < columnCount; ++column) {

			auto cell = std::make_shared<AbstactTableCell2>(
				Vector2(m_pos.x + cellWidth * column, m_pos.y + cellHeight * row),
				Vector2(cellWidth, cellHeight),
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

	auto topLeftCell = m_cells.at(0).at(0)->GetCollider();
	Vector2 TopLeftCellSize{
		topLeftCell.width,
		topLeftCell.height,
	};

	RenderTopLeft(appContext, TopLeftCellSize);
	RenderHeadline(appContext, TopLeftCellSize);
	RenderFirstColumn(appContext, TopLeftCellSize);
	RenderOtherCells(appContext, TopLeftCellSize);
	RenderOutline(appContext);

	//DrawRectangleLinesEx(m_collider, 2.0f, PURPLE);
}

void Table2::RenderTopLeft(AppContext const& appContext, Vector2 TopLeftCellSize) {

	Vector2 offset{
		0.0f,
		0.0f,
	};
	if (m_isScollable and not m_isFixedFirstColumn) {
		offset.x = m_scollOffset.x;
	}
	if (m_isScollable and not m_isFixedHeadline) {
		offset.y = m_scollOffset.y;
	}

	BeginScissorMode(
		static_cast<int>(m_collider.x),
		static_cast<int>(m_collider.y),
		static_cast<int>(TopLeftCellSize.x + 1),
		static_cast<int>(TopLeftCellSize.y + 1)
	);

	m_cells.at(0).at(0)->Render(appContext, offset);

	EndScissorMode();
}
void Table2::RenderHeadline(AppContext const& appContext, Vector2 TopLeftCellSize) {

	Vector2 offset{
		0.0f,
		0.0f,
	};
	Vector2 sOffset{
		0.0f,
		0.0f,
	};
	if (m_isScollable) {
		offset.x = m_scollOffset.x;
		if (not m_isFixedFirstColumn) {
			sOffset.x = TopLeftCellSize.x < m_scollOffset.x ? TopLeftCellSize.x : m_scollOffset.x;
		}
	}
	if (m_isScollable and not m_isFixedHeadline) {
		offset.y = m_scollOffset.y;
		sOffset.y = TopLeftCellSize.y < m_scollOffset.y ? TopLeftCellSize.y : m_scollOffset.y;
	}

	BeginScissorMode(
		static_cast<int>(m_collider.x + TopLeftCellSize.x - sOffset.x),
		static_cast<int>(m_collider.y),
		static_cast<int>(m_collider.width - TopLeftCellSize.x + sOffset.x),
		static_cast<int>(TopLeftCellSize.y + 1)
	);

	auto row = m_cells.at(0);
	for (int column = 1; column < row.size(); ++column) { // start at 1 because cell 0 is renderd in TopLeft
		row.at(column)->Render(appContext, offset);
	}

	EndScissorMode();
}
void Table2::RenderFirstColumn(AppContext const& appContext, Vector2 TopLeftCellSize) {
	Vector2 offset{
		0.0f,
		0.0f,
	};
	Vector2 sOffset{
		0.0f,
		0.0f,
	};

	if (m_isScollable and not m_isFixedFirstColumn) {
		offset.x = m_scollOffset.x;
		sOffset.x = TopLeftCellSize.x < m_scollOffset.x ? TopLeftCellSize.x : m_scollOffset.x;
	}
	if (m_isScollable) {
		offset.y = m_scollOffset.y;
		if (not m_isFixedHeadline) {
			sOffset.y = TopLeftCellSize.y < m_scollOffset.y ? TopLeftCellSize.y : m_scollOffset.y;
		}
	}

	BeginScissorMode(
		static_cast<int>(m_collider.x),
		static_cast<int>(m_collider.y + TopLeftCellSize.y - sOffset.y),
		static_cast<int>(TopLeftCellSize.x + 1),
		static_cast<int>(m_collider.height - TopLeftCellSize.y + sOffset.y)
	);

	for (int row = 1; row < m_cells.size(); ++row) { // start at 1 because cell 0 is renderd in TopLeft
		m_cells.at(row).at(0)->Render(appContext, offset);
	}

	EndScissorMode();
}
void Table2::RenderOtherCells(AppContext const& appContext, Vector2 TopLeftCellSize) {
	Vector2 offset{
		0.0f,
		0.0f,
	};
	Vector2 sOffset{
		0.0f,
		0.0f,
	};
	if (m_isScollable) {
		offset.x = m_scollOffset.x;
		if (not m_isFixedFirstColumn) {
			sOffset.x = TopLeftCellSize.x < m_scollOffset.x ? TopLeftCellSize.x : m_scollOffset.x;
		}

		offset.y = m_scollOffset.y;
		if (not m_isFixedHeadline) {
			sOffset.y = TopLeftCellSize.y < m_scollOffset.y ? TopLeftCellSize.y : m_scollOffset.y;
		}
	}

	BeginScissorMode(
		static_cast<int>(m_collider.x + TopLeftCellSize.x - sOffset.x),
		static_cast<int>(m_collider.y + TopLeftCellSize.y - sOffset.y),
		static_cast<int>(m_collider.width - TopLeftCellSize.x + sOffset.x),
		static_cast<int>(m_collider.height - TopLeftCellSize.y + sOffset.y)
		);

	for (int row = 1; row < m_cells.size(); ++row) { // start at 1 because cell 0 is renderd in TopLeft or headline
		for (int column = 1; column < m_cells.at(row).size(); ++column) { // start at 1 because cell 0 is renderd in TopLeft or first column
			m_cells.at(row).at(column)->Render(appContext, offset);
		}
	}

	EndScissorMode();
}

void Table2::RenderOutline(AppContext const& appContext) const {
	auto row = m_cells.at(m_cells.size() - 1);
	auto lastCell = row.at(row.size() - 1);
	auto lCcol = lastCell->GetCollider();
	float bottom = lCcol.y + lCcol.height;
	if (m_isScollable) { bottom -= m_scollOffset.y; }

	Rectangle outline{ 
		m_collider.x,
		m_collider.y,
		m_collider.width,
		bottom - m_collider.y,
	};

	DrawRectangleLinesEx(outline, 2.0f, PURPLE);
}
