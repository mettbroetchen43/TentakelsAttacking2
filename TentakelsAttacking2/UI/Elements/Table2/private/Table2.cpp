//
// Purpur Tentakel
// 03.04.2023
//

#include "Table2.h"
#include "HPrint.h"

int Table2::GetIndex(int row, int column) const {
	return (row * m_columnCount) + column;
}

bool Table2::IsValidIndex(int index) const {
	return 
		index < m_cells.size()
		&& index >= 0;
}

bool Table2::IsValidRow(int row) const {
	return
		row < m_rowCount
		&& row >= 0;
}

bool Table2::IsValidColumn(int column) const {
	return
		column < m_columnCount
		&& column >= 0;
}

void Table2::SetRowCount(int newRowCount) {
	if (newRowCount <= 0) { Print("tryed to set a row count inside of a table that is lower than or equal to 0.", PrintType::EXPECTED_ERROR); return; }
	
	m_rowCount = newRowCount;
}

int Table2::GetRowCount() const {
	return m_rowCount;
}

void Table2::SetColumnCount(int newColumnCount) {
	if (newColumnCount <=0) { Print("tryed to set a column count inside of a table that is lower than or equal to 0.", PrintType::EXPECTED_ERROR); return; }

	m_columnCount = newColumnCount;
}

int Table2::GetColumnCount() const {
	return m_columnCount;
}

void Table2::ResizeTable(int newRowCount, int newColumnCount) {
	SetRowCount(newRowCount);
	SetColumnCount(newColumnCount);

	ResizeTable();
}

void Table2::SetScrollable(bool isScollable) {
	m_isScollable = isScollable;
}

bool Table2::IsScollable() const {
	return m_isScollable;
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
