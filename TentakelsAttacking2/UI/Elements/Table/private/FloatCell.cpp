//
// Purpur Tentakel
// 02.10.2022
//

#include "FloatCell.h"
#include "AppContext.h"
#include "HTextProcessing.h"

Vector2 const& FloatCell::GetNeededSize() const {
	Vector2 neededSize = MeasureTextEx(
		*(AppContext::GetInstance().assetManager.GetFont()),
		std::to_string(value).c_str(),
		m_textSize,
		0.0f
	);

	return {
		(m_colider.x / neededSize.x) * m_size.x,
		(m_colider.y / neededSize.y) * m_size.y
	};
}

void FloatCell::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Cell::CheckAndUpdate(mousePosition, appContext);
	if (ShouldEdit(mousePosition)) {
		auto event = ShowFloatCellPopUpEvent(
			"Edit Number",
			this
		);
		appContext.eventManager.InvokeEvent(event);
	}
}

void FloatCell::Render(AppContext const& appContext) {
	std::string printableValue = GetPritablePlaceholderTextInColider(
		TextFormat("%.2f", value + 0.005f),
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
