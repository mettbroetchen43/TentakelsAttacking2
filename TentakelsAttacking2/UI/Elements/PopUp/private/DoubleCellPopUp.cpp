//
// Purpur Tentakel
// 04.10.2022
//

#include "DoubleCellPopUp.h"
#include "DoubleCell.h"
#include "HGeneral.h"

void DoubleCellPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([&]() {
		SetValue();
		});

	auto inputChance = std::make_shared<InputLine<double>>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.55f),
		GetElementSize(m_size, 0.9f, 0.2f),
		Alignment::MID_MID,
		15,
		resolution
		);

	auto event = NewFocusElementEvent(inputChance.get());
	appContext.eventManager.InvokeEvent(event);

	auto event2 = SelectFocusElementEvent(inputChance.get());
	appContext.eventManager.InvokeEvent(event2);
	inputChance->SetValue(m_currentCell->value);
	inputChance->SetPlaceholderText("Edit Number");

	m_elements.push_back(inputChance);
	m_inputChange = inputChance;
} 
void DoubleCellPopUp::SetValue() {
	m_currentCell->value = m_inputChange->GetValue();
	SetShouldClose();
}
void DoubleCellPopUp::CheckEnter() {
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

DoubleCellPopUp::DoubleCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title,
	AssetType infoTexture, DoubleCell* currentCell)
	: CellPopUp(pos, size, alignment, resolution, title,
		infoTexture), m_currentCell(currentCell) {

	Initialize(AppContext::GetInstance(), resolution);
}

void DoubleCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	CheckEnter();

	CellPopUp::CheckAndUpdate(mousePosition, appContext);
}
