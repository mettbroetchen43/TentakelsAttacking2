//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorCellPopUp.h"
#include "ColorCell.h"
#include "AppContext.h"
#include "GenerelHelper.h"

void ColorCellPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([&]() {
		SetValue();
		});

	auto colorPicker = std::make_shared<ColorPicker>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
		GetElementSize(m_size, 0.5f, 0.38f),
		Alignment::MID_MID,
		resolution
		);

	auto event = NewFocusElementEvent(colorPicker.get());
	appContext.eventManager.InvokeEvent(event);
	auto event2 = SelectFocusElementEvent(colorPicker.get());
	appContext.eventManager.InvokeEvent(event2);

	colorPicker->SetInitialColor(m_currentCell->value);
	colorPicker->SetCellFocuses(appContext);

	m_elements.push_back(colorPicker);
	m_colorPicker = colorPicker;
}
void ColorCellPopUp::SetValue() {
	m_currentCell->value = m_colorPicker->GetColor();
	SetShouldClose();
}
void ColorCellPopUp::CheckEnter() {
	if (!m_firstEnter and IsKeyPressed(KEY_ENTER)) {
		SetValue();
		auto event = PlaySoundEvent(SoundType::ACCEPTED);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}

	if (m_firstEnter and IsKeyUp(KEY_ENTER)) {
		m_firstEnter = false;
	}
}

ColorCellPopUp::ColorCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, AssetType infoTexture, ColorCell* currentCell)
	: CellPopUp(pos, size, alignment, resolution, title, infoTexture),
	m_currentCell(currentCell) {

	Initialize(AppContext::GetInstance(), resolution);
}

void ColorCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	CheckEnter();

	CellPopUp::CheckAndUpdate(mousePosition, appContext);
}