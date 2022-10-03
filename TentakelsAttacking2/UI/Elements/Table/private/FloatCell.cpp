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
	const char* text = TextFormat("%.2f", value + 0.005f);
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		text,
		m_textPosition,
		m_textSize,
		0.0f,
		WHITE
	);
	Cell::Render(appContext);
}
