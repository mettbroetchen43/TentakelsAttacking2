//
// Purpur Tentakel
// 02.10.2022
//

#include "ColorCell.h"
#include "AppContext.h"
#include "Table.h"

Vector2 ColorCell::GetNeededSize() const {

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
	TableCell::CheckAndUpdate(mousePosition, appContext);
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


	TableCell::Render(appContext);
}


