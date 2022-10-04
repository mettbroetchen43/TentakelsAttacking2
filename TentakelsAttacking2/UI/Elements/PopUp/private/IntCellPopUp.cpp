//
// Purpur Tentakel
// 04.10.2022
//

#include "IntCellPopUp.h"
#include "IntCell.h"

void IntCellPopUp::Initialize(AppContext const& appContext) {
	PrimitiveCellPopUp::Initialize(appContext);

	auto event = NewFocusElementEvent(&m_inputChange);
	appContext.eventManager.InvokeEvent(event);

	auto event2 = SelectFocusElementEvent(&m_inputChange);
	appContext.eventManager.InvokeEvent(event2);
	m_inputChange.SetValue(m_currentCell->value);
	m_inputChange.SetPlaceholderText("Edit Number");

	m_acceptBTN.SetOnClick([&]() {
		SetValue();
		});
}

void IntCellPopUp::SetValue() {
	m_currentCell->value = m_inputChange.GetValue();
	SetShouldClose();
}

void IntCellPopUp::CheckEnter() {
	bool validEnterClose =
		IsKeyReleased(KEY_ENTER)
		&& !m_shouldClose
		&& !m_firstEnter;
	if (validEnterClose) {
		SetValue();
	}

	if (m_firstEnter and IsKeyUp(KEY_ENTER)) {
		m_firstEnter = false;
	}
}

IntCellPopUp::IntCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title,
	AssetType infoTexture, IntCell* currentCell)
	: PrimitiveCellPopUp(pos, size, alignment, resolution, title,
		infoTexture), m_currentCell(currentCell),
	m_inputChange(InputLine<int>(
		1,
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.9f, 0.2f),
		Alignment::MID_MID,
		15,
		resolution
		)) {
	Initialize(AppContext::GetInstance());
}

void IntCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	m_inputChange.CheckAndUpdate(mousePosition, appContext);

	PrimitiveCellPopUp::CheckAndUpdate(mousePosition, appContext);

	CheckEnter();

	Close(appContext);
}
void IntCellPopUp::Render(AppContext const& appContext) {
	PrimitiveCellPopUp::Render(appContext);

	m_inputChange.Render(appContext);
}
void IntCellPopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	m_inputChange.Resize(resolution, appContext);
	PrimitiveCellPopUp::Resize(resolution, appContext);
}

