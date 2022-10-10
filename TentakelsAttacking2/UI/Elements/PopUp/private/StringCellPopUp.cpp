//
// Purpur Tentakel
// 03.10.2022
//

#include "StringCellPopUp.h"
#include "AppContext.h"
#include "HGeneral.h"
#include "StringCell.h"
#include "Table.h"

void StringCellPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([&]() {
		SetValue();
		});

	auto inputChance = std::make_shared<InputLine<std::string>>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.55f),
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
	m_currentCell->GetTable()->ResizeCells();
	SetShouldClose();
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
