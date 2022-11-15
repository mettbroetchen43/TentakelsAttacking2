//
// Purpur Tentakel
// 14.11.2022
//

#include "InitialSoundLevelPopUp.h"
#include "ClassicButton.h"
#include "SliderAndInputLine.h"
#include "Text.h"
#include "CheckBox.h"

void InitialSoundLevelPopUp::Initialize(Vector2 resolution) {
	AppContext& appContext = AppContext::GetInstance();
	
	m_slider = std::make_shared<SliderAndInputLine>(
		2, // 3
		GetElementPosition(m_pos, m_size, 0.5f, 0.7f),
		GetElementSize(m_size, 0.7f, 0.1f),
		Alignment::BOTTOM_MID,
		0,
		100,
		static_cast<int>(appContext.constants.sound.masterVolume),
		resolution
		);
	m_slider->SetActive(true, appContext);
	m_slider->SetEnabled(!appContext.constants.sound.muteVolume);
	m_slider->SetOnSave([](int value) {
		auto event = SetMasterVolumeEvent(static_cast<float>(value));
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(m_slider);

	m_checkBox = std::make_shared<CheckBox>(
		4,
		GetElementPosition(m_pos, m_size, 0.15f, 0.7f),
		GetElementSize(m_size, 0.0f, 0.04f).y,
		Alignment::TOP_LEFT,
		1,
		resolution
		);
	m_checkBox->SetChecked(appContext.constants.sound.muteVolume);
	m_checkBox->SetOnCheck([this](unsigned int, bool isChecked) {
		AppContext& appContext = AppContext::GetInstance();
		auto event = MuteMasterVolumeEvent(isChecked);
		appContext.eventManager.InvokeEvent(event);
		m_slider->SetEnabled(!isChecked);
		});
	m_elements.push_back(m_checkBox);

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.18f, 0.695f),
		GetElementSize(m_size, 0.2f, 0.3f),
		Alignment::TOP_LEFT,
		Alignment::TOP_LEFT,
		0.025f,
		"Mute",
		resolution
		));

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
