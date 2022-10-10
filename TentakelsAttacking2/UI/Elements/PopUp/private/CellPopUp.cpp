//
// Purpur Tentakel
// 04.10.2022
//

#include "CellPopUp.h"
#include "HGeneral.h"
#include "AppContext.h"

namespace {
	// Need for PopUp ctor
	std::string subTitle = "";
}

void CellPopUp::Initialize([[maybe_unused]] AppContext const& appContext,
	Vector2 resolution) {
	auto cancelBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(m_pos, m_size, 0.1f, 0.95f),
		GetElementSize(m_size, 0.3f, 0.2f),
		Alignment::BOTTOM_LEFT,
		resolution,
		"Cancel",
		SoundType::CLICKED_RELEASE_STD
		);

	auto event = NewFocusElementEvent(cancelBtn.get());
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	cancelBtn->SetOnClick([&]() {
		SetShouldClose();
		});

	m_elements.push_back(cancelBtn);
}
std::shared_ptr<ClassicButton> CellPopUp::InitializeAcceptButton(
	[[maybe_unused]] AppContext const& appContext, Vector2 resolution) {

	auto acceptBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size, 0.9f, 0.95f),
		GetElementSize(m_size, 0.3f, 0.2f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"Accept",
		SoundType::ACCEPTED
		);

	auto event = NewFocusElementEvent(acceptBtn.get());
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	m_elements.push_back(acceptBtn);

	return acceptBtn;
}

void CellPopUp::SetShouldClose() {
	m_shouldClose = true;
}

void CellPopUp::CheckEnter() {
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

void CellPopUp::Close(AppContext const& appContext) {
	if (m_shouldClose) {
		auto event = ClosePopUpEvent(this);
		appContext.eventManager.InvokeEvent(event);
	}
}

CellPopUp::CellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, AssetType infoTexture)
	: PopUp(pos, size, alignment, resolution, title, subTitle, infoTexture) {
	
	Initialize(AppContext::GetInstance(), resolution);

	if (IsKeyDown(KEY_ENTER)) {
		m_firstEnter = true;
	}
}

void CellPopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	PopUp::CheckAndUpdate(mousePosition, appContext);

	CheckEnter();

	Close(appContext);
}
