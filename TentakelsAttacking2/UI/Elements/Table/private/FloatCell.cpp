//
// Purpur Tentakel
// 02.10.2022
//

#include "FloatCell.h"
#include "AppContext.h"
#include "HTextProcessing.h"

Vector2 const& FloatCell::GetNeededSize() const {
	Vector2 textSize = MeasureTextEx(
		*(AppContext::GetInstance().assetManager.GetFont()),
		std::to_string(value).c_str(),
		m_textSize,
		0.0f
	);

	Vector2 neededSize = {
		(textSize.x / m_colider.width)* m_size.x,
		(textSize.y / m_colider.height)* m_size.y
	};

	ClampNeededSize(neededSize);
	return neededSize;
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
