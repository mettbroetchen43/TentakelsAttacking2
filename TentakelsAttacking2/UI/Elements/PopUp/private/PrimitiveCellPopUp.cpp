//
// Purpur Tentakel
// 04.10.2022
//

#include "PrimitiveCellPopUp.h"
#include "AppContext.h"

void PrimitiveCellPopUp::Initialize(AppContext const& appContext) {
	auto event = NewFocusLayerEvent();
	appContext.eventManager.InvokeEvent(event);

	auto event2 = NewFocusElementEvent(&m_acceptBTN);
	appContext.eventManager.InvokeEvent(event2);

	event2 = NewFocusElementEvent(&m_cancelBTN);
	appContext.eventManager.InvokeEvent(event2);

	m_cancelBTN.SetOnClick([&]() {
		SetShouldClose();
		});
}

void PrimitiveCellPopUp::SetShouldClose() {
	m_shouldClose = true;
}

void PrimitiveCellPopUp::Close(AppContext const& appContext) {
	if (m_shouldClose) {
		auto event = ClosePopUpEvent(this);
		appContext.eventManager.InvokeEvent(event);
	}
}

PrimitiveCellPopUp::PrimitiveCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, AssetType infoTexture)
	: CellPopUp(pos, size, alignment, resolution, title, "", infoTexture),
	m_acceptBTN(ClassicButton(
		2,
		GetElementPosition(0.9f, 0.9f),
		GetElementSize(0.3f, 0.2f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"Accept",
		AppContext::GetInstance().assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
	)),
	m_cancelBTN(ClassicButton(
		3,
		GetElementPosition(0.1f, 0.9f),
		GetElementSize(0.3f, 0.2f),
		Alignment::BOTTOM_LEFT,
		resolution,
		"Cancel",
		AppContext::GetInstance().assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::CLICKED_RELEASE_STD
	)) {
	if (IsKeyDown(KEY_ENTER)) {
		m_firstEnter = true;
	}
}

void PrimitiveCellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	m_acceptBTN.CheckAndUpdate(mousePosition, appContext);
	m_cancelBTN.CheckAndUpdate(mousePosition, appContext);

	if (IsKeyPressed(KEY_ESCAPE)) {
		SetShouldClose();
	}
}
void PrimitiveCellPopUp::Render(AppContext const& appContext) {
	PopUp::Render(appContext);

	m_acceptBTN.Render(appContext);
	m_cancelBTN.Render(appContext);
}
void PrimitiveCellPopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	m_acceptBTN.Resize(resolution, appContext);
	m_cancelBTN.Resize(resolution, appContext);
	PopUp::Resize(resolution, appContext);
}
