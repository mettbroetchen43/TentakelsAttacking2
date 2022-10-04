//
// Purpur Tentakel
// 02.10.2022
//

#include "DoubleCell.h"
#include "AppContext.h"

void DoubleCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Cell::CheckAndUpdate(mousePosition, appContext);
	if (ShouldEdit(mousePosition)) {
		auto event = ShowDoubleCellPopUpEvent(
			"Edit Number",
			this
		);
		appContext.eventManager.InvokeEvent(event);
	}
}

void DoubleCell::Render(AppContext const& appContext) {
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
