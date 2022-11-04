//
// Purpur Tentakel
// 17.10.2022
//

#include "AbstractTableCell.h"

void AbstractTableCell::CheckResizeCells(Vector2 resolution,
	AppContext const& appContext, bool resize) {
	if (resize) {
		Resize(resolution, appContext);
	}
}

void AbstractTableCell::UpdateColider(Vector2 resolution) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
}

AbstractTableCell::AbstractTableCell(unsigned int ID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution)
	:Focusable(ID), UIElement(pos, size, alignment) {
	m_colider = GetAlignedCollider(m_size, m_pos, alignment, resolution);
}

[[nodiscard]] void AbstractTableCell::SetEditable(bool editable) {
	m_editable = editable;
}
[[nodiscard]] bool AbstractTableCell::IsEnabled() const {
	return m_editable;
}

void AbstractTableCell::SetPosX(float posX, Vector2 resolution,
	AppContext const& appContext, bool resize) {

	m_pos.x = posX;
	CheckResizeCells(resolution, appContext, resize);
}
void AbstractTableCell::SetPosY(float posY, Vector2 resolution,
	AppContext const& appContext, bool resize) {

	m_pos.y = posY;
	CheckResizeCells(resolution, appContext, resize);
}

void AbstractTableCell::SetSizeX(float sizeX, Vector2 resolution,
	AppContext const& appContext, bool resize) {

	m_size.x = sizeX;
	CheckResizeCells(resolution, appContext, resize);
}
void AbstractTableCell::SetSizeY(float sizeY, Vector2 resolution,
	AppContext const& appContext, bool resize) {

	m_size.y = sizeY;
	CheckResizeCells(resolution, appContext, resize);
}