//
// Purpur Tentakel
// 15.10.2022
//

#include "DeletePlayerPopUp.h"
#include "GenerelEvents.hpp"
#include "HGeneral.h"

void DeletePlayerPopUp::Initialize(AppContext const& appContext,
	Vector2 resolution) {

	auto acceptBtn = InitializeAcceptButton(appContext, resolution);
	acceptBtn->SetOnClick([&]() {SetValue();});

	auto inputLine = std::make_shared<InputLine<int>>(
		3,
		GetElementPosition(m_pos, m_size, 0.5f, 0.45f),
		GetElementSize(m_size, 0.5f, 0.1f),
		Alignment::TOP_MID,
		5,
		resolution
		);
	inputLine->SetOnEnter([&]() {SetValue();});
	inputLine->SetPlaceholderText("Player ID");
	m_inputLine = inputLine;
	m_elements.push_back(inputLine);

	auto event = NewFocusPopUpElementEvent(inputLine.get());
	appContext.eventManager.InvokeEvent(event);

	auto selectEvent = SelectFocusPopUpElementEvent(inputLine.get());
	appContext.eventManager.InvokeEvent(selectEvent);
}

void DeletePlayerPopUp::SetValue() {
	unsigned int ID = m_inputLine->GetValue();

	auto event = DeletePlayerEvent(ID);
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	SetShouldClose();
}

DeletePlayerPopUp::DeletePlayerPopUp(Vector2 pos, Vector2 size,
	Alignment alignemnt, Vector2 resolution,
	std::string const& title, AssetType inpuTexture)
	: CellPopUp(pos, size, alignemnt, resolution,
		title, inpuTexture) {
	Initialize(AppContext::GetInstance(), resolution);
}
