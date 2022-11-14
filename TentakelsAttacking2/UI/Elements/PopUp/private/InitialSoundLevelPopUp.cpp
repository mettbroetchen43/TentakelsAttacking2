//
// Purpur Tentakel
// 14.11.2022
//

#include "InitialSoundLevelPopUp.h"
#include "ClassicButton.h"
#include "SliderAndInputLine.h"
#include "CheckBox.h"

void InitialSoundLevelPopUp::Initialize(Vector2 resolution) {
	AppContext& appContext = AppContext::GetInstance();
	
	m_slider = std::make_shared<SliderAndInputLine>(
		2, // 3
		GetElementPosition(m_pos, m_size, 0.5f, 0.75f),
		GetElementSize(m_size, 0.7f, 0.1f),
		Alignment::BOTTOM_MID,
		0,
		100,
		static_cast<int>(appContext.constants.sound.masterVolume),
		resolution
		);
	m_slider->SetActive(true, appContext);
	m_elements.push_back(m_slider);

	m_acceptBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(m_pos, m_size, 0.5f, 0.95f),
		GetElementSize(m_size, 0.2f, 0.15f),
		Alignment::BOTTOM_MID,
		resolution,
		"Accept",
		SoundType::ACCEPTED
		);
	m_acceptBtn->SetOnClick([this]() {
		AppContext::GetInstance().eventManager.InvokeEvent(ClosePopUpEvent(this));
		});
	m_elements.push_back(m_acceptBtn);
}

InitialSoundLevelPopUp::InitialSoundLevelPopUp(Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution, std::string const& title,
	std::string& subTitle)
	:PopUp(pos, size, alignment, resolution, title, subTitle, AssetType::QUESTION_MARK) {

	Initialize(resolution);
}
