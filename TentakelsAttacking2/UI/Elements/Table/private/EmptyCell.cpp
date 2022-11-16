//
// Purpur Tentakel
// 30.09.22
//

#include "EmptyCell.h"

Vector2 EmptyCell::GetNeededSize() {
	return { 0.05f,0.05f };
}

EmptyCell::EmptyCell(unsigned int ID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution)
	:AbstractTableCell(ID, pos, size, alignment, resolution) { }

void EmptyCell::CheckAndUpdate(Vector2 const&, AppContext const&) { }
void EmptyCell::Render([[maybe_unused]] AppContext const& appContext) {
	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);
};
void EmptyCell::Resize(Vector2 resolution,
	[[maybe_unused]] AppContext const& appContext) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
};

[[nodiscard]] Rectangle EmptyCell::GetCollider() const {
	return m_colider;
};
