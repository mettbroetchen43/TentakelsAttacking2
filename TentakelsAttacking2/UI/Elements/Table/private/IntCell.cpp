//
// Purpur Tentakel
// 29.09.22
//

#include "IntCell.h"
#include "AppContext.h"

void IntCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Cell::CheckAndUpdate(mousePosition, appContext);
	if (ShouldEdit(mousePosition)) {
		auto event = ShowIntCellPopUpEvent(
			"Edit Number",
			this
		);
		appContext.eventManager.InvokeEvent(event);
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
