//
// Purpur Tentakel
// 03.10.2022
//

#include "StringCellPopUp.h"
#include "UIEvents.h"
#include "AppContext.h"
#include "StringCell.h"

void StringCellPopUp::Initialize(AppContext const& appContext) {
	PrimitiveCellPopUp::Initialize(appContext);

	auto event = NewFocusElementEvent(&m_inputChange);
	appContext.eventManager.InvokeEvent(event);

	auto event2 = SelectFocusElementEvent(&m_inputChange);
	appContext.eventManager.InvokeEvent(event2);
	m_inputChange.SetValue(m_currentCell->value);
	m_inputChange.SetPlaceholderText("Edit Text");

	m_acceptBTN.SetOnClick([&]() {
		SetValue();
		});
}
void StringCellPopUp::SetValue() {
	m_currentCell->value = m_inputChange.GetValue();
	SetShouldClose();
}

void StringCellPopUp::CheckEnter() {
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

StringCellPopUp::StringCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title,
	AssetType infoTexture, StringCell* currentCell)
	: PrimitiveCellPopUp(pos, size, alignment, resolution, title, infoTexture),
	m_currentCell(currentCell),
	m_inputChange(InputLine<std::string>(
		1,
		GetElementPosition(0.5f,0.5f),
		GetElementSize(0.9f,0.2f),
		Alignment::MID_MID,
		50,
		resolution
		)) {
	Initialize(AppContext::GetInstance());
}

void StringCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	m_inputChange.CheckAndUpdate(mousePosition, appContext);

	PrimitiveCellPopUp::CheckAndUpdate(mousePosition, appContext);

	CheckEnter();

	Close(appContext);
}
void StringCellPopUp::Render(AppContext const& appContext) {
	PrimitiveCellPopUp::Render(appContext);

	m_inputChange.Render(appContext);
}
void StringCellPopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	m_inputChange.Resize(resolution, appContext);
	PrimitiveCellPopUp::Resize(resolution, appContext);
}
