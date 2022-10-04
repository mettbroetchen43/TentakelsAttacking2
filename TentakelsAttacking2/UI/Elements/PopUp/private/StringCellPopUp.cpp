//
// Purpur Tentakel
// 03.10.2022
//

#include "StringCellPopUp.h"
#include "UIEvents.h"
#include "AppContext.h"
#include "StringCell.h"

void StringCellPopUp::Initialize(AppContext const& appContext) {
	auto event = NewFocusLayerEvent();
	appContext.eventManager.InvokeEvent(event);

	auto event2 = NewFocusElementEvent(&m_inputChange);
	appContext.eventManager.InvokeEvent(event2);

	event2 = NewFocusElementEvent(&m_acceptBTN);
	appContext.eventManager.InvokeEvent(event2);

	event2 = NewFocusElementEvent(&m_cancelBTN);
	appContext.eventManager.InvokeEvent(event2);

	auto event3 = SelectFocusElementEvent(&m_inputChange);
	appContext.eventManager.InvokeEvent(event3);
	m_inputChange.SetValue(m_currentCell->value);
}

StringCellPopUp::StringCellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, std::string const& title, std::string const& subTitle,
	AssetType infoTexture, StringCell* currentCell)
	: CellPopUp(pos, size, alignment, resolution, title, subTitle, infoTexture),
	m_currentCell(currentCell),
	m_inputChange(InputLine<std::string>(
		1,
		GetElementPosition(0.5f,0.5f),
		GetElementSize(0.9f,0.2f),
		Alignment::MID_MID,
		20,
		resolution
		)),
	m_acceptBTN(ClassicButton(
		2,
		GetElementPosition(0.9f,0.9f),
		GetElementSize(0.2f,0.3f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"Accept",
		AppContext::GetInstance().assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
	)),
	m_cancelBTN(ClassicButton(
		3,
		GetElementPosition(0.1f,0.9f),
		GetElementSize(0.2f,0.3f),
		Alignment::BOTTOM_LEFT,
		resolution,
		"Cancel",
		AppContext::GetInstance().assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
	)) {
	Initialize(AppContext::GetInstance());
}

void StringCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	m_inputChange.CheckAndUpdate(mousePosition, appContext);
	m_acceptBTN.CheckAndUpdate(mousePosition, appContext);
	m_cancelBTN.CheckAndUpdate(mousePosition, appContext);
}
void StringCellPopUp::Render(AppContext const& appContext) {
	PopUp::Render(appContext);

	m_inputChange.Render(appContext);
	m_acceptBTN.Render(appContext);
	m_cancelBTN.Render(appContext);
}
void StringCellPopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	m_inputChange.Resize(resolution, appContext);
	m_acceptBTN.Resize(resolution, appContext);
	m_cancelBTN.Resize(resolution, appContext);
	PopUp::Resize(resolution, appContext);
}
