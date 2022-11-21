//
// Purpur Tentakel
// 21.11.2022
//

#include "NextTermPopUp.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "ClassicButton.h"
#include "HFocusEvents.h"

void NextTermPopUp::Initialize() {

	auto acceptBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(m_pos, m_size, 0.33f, 0.9f),
		GetElementSize(m_size, 0.2f, 0.15f),
		Alignment::BOTTOM_MID,
		m_resolution,
		"accept",
		SoundType::ACCEPTED
		);
	acceptBtn->SetOnClick([this]() {
		AppContext::GetInstance().eventManager.InvokeEvent(ValidatedNextTermEvent(true));
		this->Close();
		});
	AddFocusElement(acceptBtn.get(), true);
	m_elements.push_back(acceptBtn);

	auto cancelBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size, 0.66f, 0.9f),
		GetElementSize(m_size, 0.2f, 0.15f),
		Alignment::BOTTOM_MID,
		m_resolution,
		"cancel",
		SoundType::CLICKED_RELEASE_STD
		);
	cancelBtn->SetOnClick([this]() {
		AppContext::GetInstance().eventManager.InvokeEvent(ValidatedNextTermEvent(false));
		this->Close();
		});
	AddFocusElement(cancelBtn.get(), true);
	SelectFocusElement(cancelBtn.get(), true);
	m_elements.push_back(cancelBtn);
}

void NextTermPopUp::Close() {
	m_schouldClose = true;
	//AppContext::GetInstance().eventManager.InvokeEvent(ClosePopUpEvent(this));
}

NextTermPopUp::NextTermPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, std::string& subTitle, AssetType infoTexture)
	: PopUp(pos, size, alignment, resolution, title, subTitle, infoTexture) {

	Initialize();
}
