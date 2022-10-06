//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorCellPopUp.h"
#include "ColorCell.h"
#include "UIEvents.h"
#include "AppContext.h"

void ColorCellPopUp::Initialize(AppContext const& appContext) {
	PrimitiveCellPopUp::Initialize(appContext);

	auto event = NewFocusElementEvent(&m_colorPicker);
	appContext.eventManager.InvokeEvent(event);

	m_colorPicker.SetInitialColor(m_currentCell->value);

	m_colorPicker.SetCellFocuses(appContext);

	m_acceptBTN.SetOnClick([&]() {
		SetValue();
		});
}
void ColorCellPopUp::SetValue() {
	m_currentCell->value = m_colorPicker.GetColor();
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
	: PrimitiveCellPopUp(pos, size, alignment, resolution, title, infoTexture),
	m_currentCell(currentCell),
	m_colorPicker(
		ColorPicker(
			1,
			GetElementPosition(0.5f, 0.5f),
			GetElementSize(0.5f, 0.38f),
			Alignment::MID_MID,
			resolution
		)) {
	Initialize(AppContext::GetInstance());
}

void ColorCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	m_colorPicker.CheckAndUpdate(mousePosition, appContext);

	PrimitiveCellPopUp::CheckAndUpdate(mousePosition, appContext);

	CheckEnter();

	Close(appContext);
}
void ColorCellPopUp::Render(AppContext const& appContext) {
	PrimitiveCellPopUp::Render(appContext);

	m_colorPicker.Render(appContext);
}
void ColorCellPopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	m_colorPicker.Resize(resolution, appContext);
	PrimitiveCellPopUp::Resize(resolution, appContext);
}