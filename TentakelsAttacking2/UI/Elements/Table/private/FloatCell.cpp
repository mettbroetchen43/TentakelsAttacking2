//
// Purpur Tentakel
// 02.10.2022
//

#include "FloatCell.h"
#include "AppContext.h"

void FloatCell::CheckAndUpdate(Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) {
	if (ShouldEdit(mousePosition)) {
		// invoke Edit Event
	}
}

void FloatCell::Render(AppContext const& appContext) {
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
