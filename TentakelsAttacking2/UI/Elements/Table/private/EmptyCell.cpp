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
	:AbstractTableCell(ID, pos, size, alignment) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
}

void EmptyCell::CheckAndUpdate([[maybe_unused]] Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) { }
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

void EmptyCell::SetEditable([[maybe_unused]] bool editable) { };
[[nodiscard]] bool EmptyCell::IsEnabled() const {
	return false;
};
[[nodiscard]] Rectangle EmptyCell::GetCollider() const {
	return m_colider;
};
