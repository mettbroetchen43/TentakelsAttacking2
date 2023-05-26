//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorCellPopUp.h"
#include "AppContext.h"
#include "HGeneral.h"
#include "HFocusEvents.h"

void ColorCellPopUp::Initialize(AppContext_ty_c appContext,
	Vector2 resolution, Color currentColor) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([this]() {
		this->SetValue();
		});

	auto colorPicker = std::make_shared<ColorPicker>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
		GetElementSize(m_size, 0.5f, 0.38f),
		Alignment::MID_MID,
		resolution,
		true
		);

	AddFocusElement(colorPicker.get(), true);
	SelectFocusElement(colorPicker.get(), true);

	colorPicker->SetInitialColor(currentColor);
	colorPicker->SetCellFocuses(appContext);

	m_elements.push_back(colorPicker);
	m_colorPicker = colorPicker;
}
void ColorCellPopUp::SetValue() {
	m_onClick(m_colorPicker->GetColor());
	SetShouldClose();
}

ColorCellPopUp::ColorCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, AssetType infoTexture, Color currentColor,
	std::function<void(Color)> onClick)
	: CellPopUp{ pos, size, alignment, resolution, title, infoTexture },
	m_onClick{ onClick } {

	Initialize(AppContext::GetInstance(), resolution, currentColor);
}