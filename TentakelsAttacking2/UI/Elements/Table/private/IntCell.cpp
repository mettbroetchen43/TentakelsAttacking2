//
// Purpur Tentakel
// 29.09.22
//

#include "IntCell.h"
#include "AppContext.h"
#include "HTextProcessing.h"

Vector2 IntCell::GetNeededSize() const {
	Vector2 textSize = MeasureTextEx(
		*(AppContext::GetInstance().assetManager.GetFont()),
		std::to_string(value).c_str(),
		m_textSize,
		0.0f
	);

	return CalculateNeededSize(textSize);
}

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
