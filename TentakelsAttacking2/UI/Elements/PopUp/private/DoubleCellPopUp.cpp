//
// Purpur Tentakel
// 04.10.2022
//

#include "DoubleCellPopUp.h"
#include "DoubleCell.h"

void DoubleCellPopUp::Initialize(AppContext const& appContext) {
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
void DoubleCellPopUp::SetValue() {
	m_currentCell->value = m_inputChange.GetValue();
	SetShouldClose();
}

void DoubleCellPopUp::CheckEnter() {
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

DoubleCellPopUp::DoubleCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title,
	AssetType infoTexture, DoubleCell* currentCell)
	: PrimitiveCellPopUp(pos, size, alignment, resolution, title,
		infoTexture), m_currentCell(currentCell),
	m_inputChange(InputLine<double>(
		1,
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.9f, 0.2f),
		Alignment::MID_MID,
		15,
		resolution
		)) {
	Initialize(AppContext::GetInstance());
}

void DoubleCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	m_inputChange.CheckAndUpdate(mousePosition, appContext);

	PrimitiveCellPopUp::CheckAndUpdate(mousePosition, appContext);

	CheckEnter();

	Close(appContext);
}
void DoubleCellPopUp::Render(AppContext const& appContext) {
	PrimitiveCellPopUp::Render(appContext);

	m_inputChange.Render(appContext);
}
void DoubleCellPopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	m_inputChange.Resize(resolution, appContext);
	PrimitiveCellPopUp::Resize(resolution, appContext);
}
