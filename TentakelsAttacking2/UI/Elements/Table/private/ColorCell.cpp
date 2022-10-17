//
// Purpur Tentakel
// 02.10.2022
//

#include "ColorCell.h"
#include "AppContext.h"
#include "Table.h"

Vector2 ColorCell::GetNeededSize() const {
	Vector2 neededSize =  { 0.05f, 0.1f };
	ClampNeededSize(neededSize);
	return neededSize;
}

void ColorCell::SetValue(Color value, bool resize) {
	m_value = value;

	if (resize) {
		m_table->ResizeCells();
	}
}
Color ColorCell::GetValue() const {
	return m_value;
}

void ColorCell::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	Cell::CheckAndUpdate(mousePosition, appContext);
	if (ShouldEdit(mousePosition)) {
		auto event = ShowColorCellPopUpEvent(
			"Change Color",
			m_value,
			[&](Color color) {SetValue(color);}
		);
		appContext.eventManager.InvokeEvent(event);
	}
}

void ColorCell::Render(AppContext const& appContext) {
	float spacing = 5.0f;
	Rectangle toFill = {
		 m_colider.x + spacing,
		 m_colider.y + spacing,
		 m_colider.width - 2 * spacing,
		 m_colider.height - 2 * spacing
	};
	DrawRectanglePro(
		toFill,
		Vector2(0.0f, 0.0f),
		0.0f,
		m_value
	);

	Cell::Render(appContext);
}


