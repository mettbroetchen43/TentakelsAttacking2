//
// Purpur Tentakel
// 02.10.2022
//

#include "DoubleCell.h"
#include "AppContext.h"
#include "TextProcessing.h"

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
	std::string printableValue = GetPritablePlaceholderTextInColider(
		std::to_string(value),
		m_textSize,
		m_colider,
		appContext
	);
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		printableValue.c_str(),
		m_textPosition,
		m_textSize,
		0.0f,
		WHITE
	);
	Cell::Render(appContext);
}
