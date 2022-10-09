//
// Purpur Tentakel
// 03.10.2022
//

#include "StringCellPopUp.h"
#include "AppContext.h"
#include "GenerelHelper.h"
#include "StringCell.h"

void StringCellPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([&]() {
		SetValue();
		});

	auto inputChance = std::make_shared<InputLine<std::string>>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.5f),
		GetElementSize(m_size, 0.9f, 0.2f),
		Alignment::MID_MID,
		50,
		resolution
		);

	auto event = NewFocusElementEvent(inputChance.get());
	appContext.eventManager.InvokeEvent(event);

	auto event2 = SelectFocusElementEvent(inputChance.get());
	appContext.eventManager.InvokeEvent(event2);
	inputChance->SetValue(m_currentCell->value);
	inputChance->SetPlaceholderText("Edit Text");

	m_elements.push_back(inputChance);
	m_inputChange = inputChance;

}
void StringCellPopUp::SetValue() {
	m_currentCell->value = m_inputChange->GetValue();
	SetShouldClose();
}

void StringCellPopUp::CheckEnter() {
	bool validEnterClose =
		IsKeyReleased(KEY_ENTER)
		&& !m_shouldClose
		&& !m_firstEnter;
	if (validEnterClose) {
		AppContext::GetInstance().soundManager.PlaySound(SoundType::ACCEPTED);
		SetValue();
	}

	if (m_firstEnter and IsKeyUp(KEY_ENTER)) {
		m_firstEnter = false;
	}
}

StringCellPopUp::StringCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title,
	AssetType infoTexture, StringCell* currentCell)
	: CellPopUp(pos, size, alignment, resolution, title, infoTexture),
	m_currentCell(currentCell){

	Initialize(AppContext::GetInstance(), resolution);
}

void StringCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	CheckEnter();

	CellPopUp::CheckAndUpdate(mousePosition, appContext);
}
