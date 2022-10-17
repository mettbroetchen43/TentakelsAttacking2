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

AbstractTableCell::AbstractTableCell(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment)
	:Focusable(ID), UIElement(pos, size, alignment) { }

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