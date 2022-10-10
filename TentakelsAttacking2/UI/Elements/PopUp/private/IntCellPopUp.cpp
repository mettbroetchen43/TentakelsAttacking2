//
// Purpur Tentakel
// 04.10.2022
//

#include "IntCellPopUp.h"
#include "IntCell.h"
#include "HGeneral.h"
#include "Table.h"

void IntCellPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([&]() {
		SetValue();
	});

	auto inputChange = std::make_shared<InputLine<int>>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.55f),
		GetElementSize(m_size, 0.9f, 0.2f),
		Alignment::MID_MID,
		9,
		resolution
		);

	auto event = NewFocusElementEvent(inputChange.get());
	appContext.eventManager.InvokeEvent(event);

	auto event2 = SelectFocusElementEvent(inputChange.get());
	appContext.eventManager.InvokeEvent(event2);
	inputChange->SetValue(m_currentCell->value);
	inputChange->SetPlaceholderText("Edit Number");

	m_elements.push_back(inputChange);
	m_inputChange = inputChange;
}

void IntCellPopUp::SetValue() {
	m_currentCell->value = m_inputChange->GetValue();
	m_currentCell->GetTable()->ResizeCells();
	SetShouldClose();
}

void IntCellPopUp::CheckEnter() {
	bool validEnterClose =
		IsKeyReleased(KEY_ENTER)
		&& !m_shouldClose
		&& !m_firstEnter;
	if (validEnterClose) {
		auto event = PlaySoundEvent(SoundType::ACCEPTED);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		SetValue();
	}

	if (m_firstEnter and IsKeyUp(KEY_ENTER)) {
		m_firstEnter = false;
	}
}

IntCellPopUp::IntCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title,
	AssetType infoTexture, IntCell* currentCell)
	: CellPopUp(pos, size, alignment, resolution, title,
		infoTexture), m_currentCell(currentCell){

	Initialize(AppContext::GetInstance(), resolution);
}

void IntCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	CheckEnter();

	CellPopUp::CheckAndUpdate(mousePosition, appContext);
}

