//
// Purpur Tentakel
// 03.04.2023
//

#include "Table2.h"
#include "HInput.h"
#include "Slider.h"
#include "AppContext.h"


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

	if (m_isScrollable) {

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
			cell->CalculateTextSize();
		}
	}

	if (m_isScrollable) {
		ScrollMove(m_absoluteScollingOffset);
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

void Table2::ResizeTable() {
	bool needResize =
		m_rowCount != m_cells.size() + 1
		and m_columnCount != m_cells.at(0).size() + 1
		and m_setScrollable != m_isScrollable;
	if (not needResize) { return; }

	m_isScrollable = m_setScrollable;

	// rows
	if (m_cells.size() == m_rowCount) { /* nothing */ }
	else if (m_cells.size() < m_rowCount) {
		while (m_cells.size() < m_rowCount) {
			AddLastRow<std::string>("");
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
			AddLastColumn<std::string>("");
		}
	}
	else if (row.size() > m_columnCount) {
		while (row.size() > m_columnCount) {
			RemoveLastColum();
		}
	}

	UpdateCellFocusID();
	UpdateCellPositionAndSize();
	CalculateSlider();
}
void Table2::UpdateHeadlinePosition() {
	if (m_setFixedHeadline == m_isFixedHeadline) { return; }
	m_isFixedHeadline = m_setFixedHeadline;

	if (m_isFixedHeadline) {
		for (auto cell : m_cells.at(0)) {
			auto col = cell->GetCollider();
			col.y = m_collider.y;
			cell->SetCollider(col);
			cell->CalculateTextSize();
		}
	}
	else {
		if (m_rowCount < 2) { Print("not able to move headline", PrintType::EXPECTED_ERROR); return; }
		float height = m_cells.at(0).at(0)->GetCollider().height;
		float pos = m_cells.at(1).at(0)->GetCollider().y;
		for (auto cell : m_cells.at(0)) {
			auto col = cell->GetCollider();
			col.y = pos - height;
			cell->SetCollider(col);
			cell->CalculateTextSize();
		}
	}

}
void Table2::UpdateFirstRowPosition() {
	if (m_setFixedFirstColumn == m_isFixedFirstColumn) { return; }
	m_isFixedFirstColumn = m_setFixedFirstColumn;

	if (m_isFixedFirstColumn) {
		for (int row = 0; row < m_cells.size(); ++row) {
			auto cell = m_cells.at(row).at(0);
			auto col = cell->GetCollider();
			col.x = m_collider.x;
			cell->SetCollider(col);
			cell->CalculateTextSize();
		}
	}
	else {
		if (m_columnCount < 2) { Print("not able to move first row", PrintType::EXPECTED_ERROR); return; }

		float width = m_cells.at(0).at(0)->GetCollider().width;
		float pos = m_cells.at(0).at(1)->GetCollider().x;

		for (int row = 0; row < m_cells.size(); ++row) {
			auto cell = m_cells.at(row).at(0);
			auto col = cell->GetCollider();
			col.x = pos - width;
			cell->SetCollider(col);
			cell->CalculateTextSize();
		}
	}
}

void Table2::CheckAndUpdateClickCell(Vector2 const& mousePositon, AppContext const& appContext) {
	if (not CheckCollisionPointRec(mousePositon, m_collider)) { return; }
	if (not IsMouseButtonPressed(0)) { return; }

	auto cell = m_cells.at(0).at(0);
	if (cell->IsColliding(mousePositon)) {
		goto clicked;
	}

	for (int row = 1; row < m_rowCount; ++row) {
		cell = m_cells.at(row).at(0);
		if (cell->IsColliding(mousePositon)) {
			goto clicked;
		}
	}

	for (int column = 1; column < m_columnCount; ++column) {
		cell = m_cells.at(0).at(column);
		if (cell->IsColliding(mousePositon)) {
			goto clicked;
		}
	}

	for (int row = 1; row < m_rowCount; ++row) {
		for (int column = 1; column < m_columnCount; ++column) {
			cell = m_cells.at(row).at(column);
			if (cell->IsColliding(mousePositon)) {
				goto clicked;
			}
		}
	}

clicked:
	cell->Clicked(mousePositon, appContext);
	return;
}

void Table2::CheckAndUpdateScroll(Vector2 const& mousePosition) {
	if (not m_isScrollable) { return; }
	if (not CheckCollisionPointRec(mousePosition, m_collider)) { return; } // check if collider is maybe to big

	float mouseWheel = GetMouseWheelMove();
	if (mouseWheel == 0.0f) { return; }

	Vector2 offset{ 0.0f,0.0f };
	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		offset.x = mouseWheel * m_scroll_speed * m_resolution.x;
	}
	else {
		offset.y = mouseWheel * m_scroll_speed * m_resolution.y;
	}

	ClampScroollOffset(offset);
	ScrollMove(offset);
	m_absoluteScollingOffset.x += offset.x;
	m_absoluteScollingOffset.y += offset.y;

	Vector2 size = GetAbsoluteSize();
	m_horizontalSlider->SetButtonPosition((-m_absoluteScollingOffset.x / (size.x - m_collider.width)) * 100);
	m_verticalSlider->SetButtonPosition((-m_absoluteScollingOffset.y / (size.y - m_collider.height)) * 100);

	if (IsNestedFocus()) {
		auto event = RenderFocusEvent(false);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
Vector2 Table2::GetAbsoluteSize() const {

	Vector2 toReturn{ 0.0f,0.0f };

	for (auto cell : m_cells.at(0)) {
		toReturn.x += cell->GetCollider().width;
	}
	for (int i = 0; i < m_rowCount; ++i) {
		auto cell = m_cells.at(i).at(0);
		toReturn.y += cell->GetCollider().height;
	}

	return toReturn;
}
void Table2::ClampScroollOffset(Vector2& offset) {
	if (m_rowCount < 2) { Print("not enough rows in table for clamping", PrintType::EXPECTED_ERROR); return; }
	if (m_columnCount < 2) { Print("not enough columns in table for clamping", PrintType::EXPECTED_ERROR); return; }

	// get cells
	auto cellTopLeft = m_cells.at(0).at(0)->GetCollider();
	auto cellSecondTopLeft = m_cells.at(1).at(1)->GetCollider();
	auto cellBottomLeft = m_cells.at(m_rowCount - 1).at(m_columnCount - 1)->GetCollider();

	// clamp left x
	float cell = cellSecondTopLeft.x + offset.x;
	float table = m_collider.x + cellTopLeft.width;
	if (cell > table) { offset.x -= cell - table; }

	// clamp right x
	cell = cellBottomLeft.x + cellBottomLeft.width + offset.x;
	table = m_collider.x + m_collider.width;
	if (cell < table) { offset.x += table - cell; }

	// clamp top y
	cell = cellSecondTopLeft.y + offset.y;
	table = m_collider.y + cellTopLeft.height;
	if (cell > table) { offset.y -= cell - table; }

	// clamp bottom y
	cell = cellBottomLeft.y + cellBottomLeft.height + offset.y;
	if (m_activeHorizontalSlider) { cell += cellBottomLeft.height; }
	table = m_collider.y + m_collider.height;
	if (cell < table) { offset.y += table - cell; }

}
void Table2::ScrollFocused() {
	if (not m_isScrollable) { return; }
	if (not IsNestedFocus()) { return; }

	std::shared_ptr<AbstractTableCell2> cell = nullptr;
	for (int row = 0; row < m_cells.size(); ++row) {
		for (int column = 0; column < m_cells.at(row).size(); ++column) {
			auto cCell = m_cells.at(row).at(column);
			if (cCell->IsFocused()) {
				cell = cCell;
				goto out;
			}
		}
	}
out:
	if (not cell) { return; }

	auto col = cell->GetCollider();
	bool cellInCollider =
		m_collider.x < col.x  // left
		and m_collider.x + m_collider.width > col.x + col.width  // right
		and m_collider.y < col.y  // top
		and m_collider.y + m_collider.height > col.y + col.height;  // bottom
	if (cellInCollider) { return; }

	Vector2 offset{ 0.0f,0.0f };
	if (m_collider.x > col.x) {  // left
		offset.x = m_collider.x - col.x;
	}
	else if (m_collider.x + m_collider.width < col.x + col.width) { // right
		offset.x = (m_collider.x + m_collider.width) - (col.x + col.width);
	}

	if (m_collider.y > col.y) {  // top
		offset.y = m_collider.y - col.y;
	}
	else if (m_collider.y + m_collider.height < col.y + col.height) {  // bottom
		offset.y = (m_collider.y + m_collider.height) - (col.y + col.height);
	}

	ScrollMove(offset);
	m_absoluteScollingOffset.x += offset.x;
	m_absoluteScollingOffset.y += offset.y;
}
void Table2::ScollPercent(float percent, bool isHorisonzal) {

	auto size = GetAbsoluteSize();
	Vector2 offset{ 0.0f,0.0f };

	if (isHorisonzal) {
		size.x -= m_collider.width;
		size.x *= percent / 100;
		offset.x = -(size.x + m_absoluteScollingOffset.x);
	}
	else {
		size.y -= m_collider.height;
		size.y *= percent / 100;
		offset.y = -(size.y + m_absoluteScollingOffset.y);
	}

	ClampScroollOffset(offset);
	ScrollMove(offset);
	m_absoluteScollingOffset.x += offset.x;
	m_absoluteScollingOffset.y += offset.y;

	if (IsNestedFocus()) {
		auto event = RenderFocusEvent(false);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void Table2::ScrollMove(Vector2 const& offset) {
	for (int row = 0; row < m_cells.size(); ++row) {
		for (int column = 0; column < m_cells.at(row).size(); ++column) {
			Vector2 individualOffset{ offset };
			if (row == 0 and m_isFixedHeadline) { individualOffset.y = 0.0f; }
			if (column == 0 and m_isFixedFirstColumn) { individualOffset.x = 0.0f; }

			auto cell = m_cells.at(row).at(column);
			auto collider = cell->GetCollider();
			collider.x += individualOffset.x;
			collider.y += individualOffset.y;
			cell->SetCollider(collider);
			cell->CalculateTextSize();
		}
	}
}
void Table2::CalculateSlider() {

	float width{ 0.0f };
	for (auto cell : m_cells.at(0)) {
		width += cell->GetSize().x;
	}
	m_activeHorizontalSlider = width > m_size.x + m_columnCount * 0.001f;
	m_horizontalSlider->SetAboluteDimension(width);

	float height{ 0.0f };
	for (int i = 0; i < m_rowCount; ++i) {
		auto cell = m_cells.at(0).at(1);
		height += cell->GetSize().y;
	}
	m_activeVerticalSlider = height > m_size.y + m_rowCount * 0.001f;
	m_verticalSlider->SetAboluteDimension(height);
}

void Table2::CalculateHoverHighlighted(Vector2 mousePosition) {
	Vec2<int> newPosition{ -1,-1 };
	if (not m_isHoveredHighlighted) { goto found; }
	if (not CheckCollisionPointRec(mousePosition, m_collider)) { goto found; }

	if (m_cells.at(0).at(0)->IsColliding(mousePosition)) { newPosition = { 0, 0 }; goto found; }

	for (int column = 1; column < m_columnCount; ++column) {
		auto cell = m_cells.at(0).at(column);
		if (cell->IsColliding(mousePosition)) { newPosition = { 0, column }; goto found; }
	}

	for (int row = 1; row < m_rowCount; ++row) {
		auto cell = m_cells.at(row).at(0);
		if (cell->IsColliding(mousePosition)) { newPosition = { row, 0 }; goto found; }
	}

	for (int row = 1; row < m_rowCount; ++row){
		for (int column = 1; column < m_columnCount; ++column) {
			auto cell = m_cells.at(row).at(column);
			if (cell->IsColliding(mousePosition)) { newPosition = { row, column }; goto found; }
		}
	}

found:
	if (m_currentHighlighted == newPosition) { return; }

	SetHighlightBeackground(true);
	m_currentHighlighted = newPosition;
	SetHighlightBeackground(false);
}
void Table2::SetHighlightBeackground(bool reset) {
	Color newColor = reset ? BLACK : HOVERGREY;

	if (m_currentHighlighted.x >= 0) {
		for (auto cell : m_cells.at(m_currentHighlighted.x)) {
			cell->SetBackgoundColor(newColor);
		}
	}

	if (m_currentHighlighted.y >= 0) {
		for (int i = 0; i < m_rowCount; ++i) {
			auto cell = m_cells.at(i).at(m_currentHighlighted.y);
			cell->SetBackgoundColor(newColor);
		}
	}
}

void Table2::RenderTopLeft(AppContext const& appContext) {
	m_cells.at(0).at(0)->Render(appContext);
}
void Table2::RenderHeadline(AppContext const& appContext) {

	auto row = m_cells.at(0);
	for (int column = 1; column < row.size(); ++column) { // start at 1 because cell 0 is renderd in TopLeft
		row.at(column)->Render(appContext);
	}
}
void Table2::RenderFirstColumn(AppContext const& appContext) {

	for (int row = 1; row < m_cells.size(); ++row) { // start at 1 because cell 0 is renderd in TopLeft
		m_cells.at(row).at(0)->Render(appContext);
	}
}
void Table2::RenderOtherCells(AppContext const& appContext) {

	for (int row = 1; row < m_cells.size(); ++row) { // start at 1 because cell 0 is renderd in TopLeft or headline
		for (int column = 1; column < m_cells.at(row).size(); ++column) { // start at 1 because cell 0 is renderd in TopLeft or first column
			m_cells.at(row).at(column)->Render(appContext);
		}
	}
}
void Table2::RenderOutline() const {

	DrawRectangleLinesEx(
		m_collider,
		2.0f,
		WHITE
	);
}

Table2::Table2(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID,
	int rowCount, int columnCount, Vector2 minCellSize, float scrollSpeed)
	: UIElement(pos, size, alignment, resolution), Focusable(focusID),
	m_rowCount(rowCount), m_columnCount(columnCount), m_minCellSize(minCellSize), m_scroll_speed(scrollSpeed) {


	m_minCellSize = {
		m_minCellSize.x * m_size.x,
		m_minCellSize.y * m_size.y
	};
	float cellWidth = m_size.x / m_columnCount;
	float cellHeight = m_size.y / m_rowCount;

	m_cells.clear();
	for (int row = 0; row < m_rowCount; ++row) {

		auto line = std::vector<std::shared_ptr<AbstractTableCell2>>();
		for (int column = 0; column < columnCount; ++column) {

			auto cell = std::make_shared<TableCell2<std::string>>(
				Vector2(m_pos.x + cellWidth * column, m_pos.y + cellHeight * row),
				Vector2(cellWidth, cellHeight),
				Alignment::TOP_LEFT,
				m_resolution,
				row * columnCount + column,
				"",
				[this](AbstractTableCell2 const* cell, std::string oldValue, std::string newValue)
				{this->CellUpdated < std::string > (cell, oldValue, newValue); }
			);

			line.push_back(cell);
		}
		m_cells.push_back(line);
	}

	m_editableRowsColumns = {
		std::vector<bool>(m_rowCount,true),
		std::vector<bool>(m_columnCount,true)
	};

	m_verticalSlider = std::make_shared<Slider>(
		GetElementPosition(m_pos, m_size, 0.995f, 0.5f),
		GetElementSize(m_size, 0.01f, 0.9f),
		Alignment::MID_RIGHT,
		m_resolution,
		false,
		20.0f
	);
	m_verticalSlider->SetOnSlide([this](float percent) {
		this->ScollPercent(percent, false);
		});
	m_horizontalSlider = std::make_shared<Slider>(
		GetElementPosition(m_pos, m_size, 0.5f, 0.99f),
		GetElementSize(m_size, 0.9f, 0.02f),
		Alignment::BOTTOM_MID,
		m_resolution,
		true,
		20.0f
	);
	m_horizontalSlider->SetOnSlide([this](float percent) {
		this->ScollPercent(percent, true);
		});
	CalculateSlider();

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


void Table2::RemoveSpecificRow(int row) {
	if (!IsValidRow(row)) { Print("row out of range", PrintType::ERROR), throw std::out_of_range("row index"); }

	m_cells.erase(m_cells.begin() + row);
	m_editableRowsColumns.at(0).erase(m_editableRowsColumns.at(0).begin() + row);
	--m_rowCount;
}
void Table2::RemoveLastRow() {
	RemoveSpecificRow(static_cast<int>(m_cells.size() - 1));
}
void Table2::RemoveSpecificColumn(int column) {
	if (!IsValidColumn(column)) { Print("column index out of range", PrintType::ERROR), throw std::out_of_range("column index"); }

	for (auto& row : m_cells) {
		row.erase(row.begin() + column);
	}

	m_editableRowsColumns.at(1).erase(m_editableRowsColumns.at(1).begin() + column);
	--m_columnCount;
}
void Table2::RemoveLastColum() {
	if (m_cells.size() == 0) { Print("no rows in table", PrintType::ERROR), throw std::out_of_range("no rows"); }
	RemoveSpecificColumn(static_cast<int>(m_cells.at(0).size() - 1));
}

void Table2::SetHighlightHover(bool isHoveredHighlighted) {
	m_isHoveredHighlighted = isHoveredHighlighted;
}
bool Table2::IsHighlighedHover() const {
	return m_isHoveredHighlighted;
}

void Table2::SetScrollable(bool isScollable) {
	m_setScrollable = isScollable;
}
bool Table2::IsScollable() const {
	return m_isScrollable;
}

void Table2::SetSingleEditable(int row, int column, bool isEditable) {
	if (!IsValidIndex(row, column)) { Print("row or column index out auf range", PrintType::ERROR); throw std::out_of_range("invalid index"); }

	m_cells.at(row).at(column)->SetEditable(isEditable);
}
bool Table2::IsSingleEditable(int row, int column) const {
	if (!IsValidIndex(row, column)) { Print("row or column index out auf range", PrintType::ERROR); throw std::out_of_range("invalid index"); }
	return m_cells.at(row).at(column)->IsEditable();
}

void Table2::SetAllEditable(bool isEditable) noexcept {
	for (auto& row : m_cells) {
		for (auto& cell : row) {
			cell->SetEditable(isEditable);
		}
	}
	for (int i = 0; i < m_editableRowsColumns.size(); ++i) {
		for (int j = 0; j < m_editableRowsColumns.at(i).size(); ++j) {
			m_editableRowsColumns.at(i).at(j) = isEditable;
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
	m_editableRowsColumns.at(0).at(row) = isEditable;
}
bool Table2::IsRowEditable(int row) const {
	if (!IsValidRow(row)) { Print("row out of range", PrintType::ERROR), throw std::out_of_range("row index"); }

	return m_editableRowsColumns.at(0).at(row);
}

void Table2::SetColumnEditable(int column, bool isEditable) {
	if (!IsValidColumn(column)) { Print("column out of Range", PrintType::ERROR); throw std::out_of_range("column index"); }

	for (auto& row : m_cells) {
		row.at(column)->SetEditable(isEditable);
	}
	m_editableRowsColumns.at(1).at(column) = isEditable;
}
bool Table2::IsColumnEditable(int column) const {
	if (!IsValidColumn(column)) { Print("column out of Range", PrintType::ERROR); throw std::out_of_range("column index"); }

	return m_editableRowsColumns.at(1).at(column);
}

void Table2::SetFixedHeadline(bool isFixedHeadline) {
	m_setFixedHeadline = isFixedHeadline;
}
bool Table2::IsFixedHeadline() const {
	return m_isFixedHeadline;
}

void Table2::SetFixedFirstColumn(bool isFixedFirstColumn) {
	m_setFixedFirstColumn = isFixedFirstColumn;
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

	ResizeTable();
	UpdateHeadlinePosition();
	UpdateFirstRowPosition();
	CheckAndUpdateScroll(mousePosition);

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

	if (m_activeHorizontalSlider) {
		m_horizontalSlider->CheckAndUpdate(mousePosition, appContext);
	}
	if (m_activeVerticalSlider) {
		m_verticalSlider->CheckAndUpdate(mousePosition, appContext);
	}

	for (auto const& row : m_cells) {
		for (auto const& cell : row) {
			cell->CheckAndUpdate(mousePosition, appContext);
		}
	}
	bool sliderHover =
		m_activeHorizontalSlider and m_horizontalSlider->IsColliding(mousePosition)
		or m_activeVerticalSlider and m_verticalSlider->IsColliding(mousePosition);
	if (not sliderHover) {
		CheckAndUpdateClickCell(mousePosition, appContext);
	}

	if (IsKeyPressed(KEY_TAB)) {
		ScrollFocused();
	}

	CalculateHoverHighlighted(mousePosition);
}
void Table2::Render(AppContext const& appContext) {

	BeginScissorMode(
		static_cast<int>(m_collider.x),
		static_cast<int>(m_collider.y),
		static_cast<int>(m_collider.width),
		static_cast<int>(m_collider.height)
	);

	RenderOtherCells(appContext);
	RenderFirstColumn(appContext);
	RenderHeadline(appContext);
	RenderTopLeft(appContext);
	RenderOutline();

	EndScissorMode();

	if (m_activeHorizontalSlider) {
		m_horizontalSlider->Render(appContext);
	}
	if (m_activeVerticalSlider) {
		m_verticalSlider->Render(appContext);
	}
}

