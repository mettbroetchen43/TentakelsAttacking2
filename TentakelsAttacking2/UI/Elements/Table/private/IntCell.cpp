//
// Purpur Tentakel
// 29.09.22
//

#include "IntCell.h"
#include "AppContext.h"

void IntCell::CheckAndUpdate(Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) {
	if (ShouldEdit(mousePosition)) {
		// invoke Event
	}
}

void IntCell::Render(AppContext const& appContext) {
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		std::to_string(value).c_str(),
		m_textPosition,
		m_textSize,
		0.0f,
		WHITE
	);
	Cell::Render(appContext);
}
