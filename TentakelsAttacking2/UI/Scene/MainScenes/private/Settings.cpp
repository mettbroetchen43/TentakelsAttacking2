//
// Purpur Tentakel
// 01.11.2022
//

#include "Settings.h"
#include "Title.h"
#include "Text.h"
#include "ClassicButton.h"
#include "SceneType.h"
#include "GameEventSettings.h"
#include "SliderAndInputLine.h"
#include "CheckBox.h"
#include "DropDown.h"
#include "Line.h"
#include "AppContext.h"
#include "UIEvents.hpp"

void SettingsScene::Initialize() {

	AppContext& appContext = AppContext::GetInstance();

	float elementY = 0.3f;
	float sliderOffset = 0.04f;
	float elementOffset = 0.15f;

	// title
	m_elements.push_back(std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		m_resolution,
		false,
		appContext
		));

	// headline
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.5f, 0.2f),
		GetElementSize(0.3f, 0.1f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.07f,
		"Settings"
		));

	// line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.5f, elementY),
		GetElementSize(0.0f, 0.65f),
		Alignment::TOP_MID,
		m_resolution,
		2.0f
		));

	// events
	auto eventSettings = std::make_shared<GameEventSettings>(
		1,
		GetElementPosition(0.25f, elementY),
		GetElementSize(0.25f, 0.5f),
		Alignment::TOP_MID,
		m_resolution
		);
	eventSettings->SetActive(true, appContext);
	m_elements.push_back(eventSettings);

	// volume
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Volume:"
		));

	m_volume = std::make_shared<SliderAndInputLine>(
		100,
		GetElementPosition(0.75f, elementY + sliderOffset),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		0,
		100,
		static_cast<int>(appContext.constants.sound.masterVolume)
		);
	m_volume->SetActive(true, appContext);
	m_volume->SetEnabled(!appContext.constants.sound.muteVolume);
	m_volume->SetOnSave([](int value) {
		auto event = SetMasterVolumeEvent(static_cast<float>(value));
	AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(m_volume);

	auto muteCB = std::make_shared<CheckBox>(
		102,
		GetElementPosition(0.55f, elementY + sliderOffset + 0.05f),
		GetElementSize(0.0f, 0.02f).y,
		Alignment::TOP_LEFT,
		m_resolution,
		1
		);
	muteCB->SetChecked(appContext.constants.sound.muteVolume);
	muteCB->SetOnCheck([this](unsigned int, bool isChecked) {
		AppContext& appContext = AppContext::GetInstance();
	auto event = MuteMasterVolumeEvent(isChecked);
	appContext.eventManager.InvokeEvent(event);
	m_volume->SetEnabled(!isChecked);
		});
	m_elements.push_back(muteCB);

	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.565f, elementY + sliderOffset + 0.05f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		"Mute"
		));

	elementY += elementOffset;
	// last round
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"ca. Last Round:"
		));

	auto lastRound = std::make_shared<SliderAndInputLine>(
		200,
		GetElementPosition(0.75f, elementY + sliderOffset),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		static_cast<int>(appContext.constants.global.minRounds),
		static_cast<int>(appContext.constants.global.maxRounds),
		static_cast<int>(appContext.constants.global.currentTargetRound)
		);
	lastRound->SetActive(true, appContext);
	lastRound->SetOnSave([](int value) {
		auto event = SetCurrentLastRoundEvent(value);
	AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(lastRound);

	elementY += elementOffset;

	// drop down
	auto resolution_text = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.02f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		"this setting is only visible in window mode"
		);
	m_elements.push_back(resolution_text);

	elementY += 0.02f;
	auto resolution = std::make_shared<DropDown>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		0.25f,
		300,
		301,
		appContext.constants.window.GetAllResolutionsAsString()
		);
	resolution->SetCurrentElementByID(static_cast<unsigned int>(appContext.constants.window.current_resolution) + 1);
	resolution->SetOnSave([this](unsigned int ID) {
		auto event = SetNewResolutionEvent(static_cast<Resolution>(ID - 1));
	AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(resolution);

	// btn
	auto finishBtn = std::make_shared<ClassicButton>(
		400,
		GetElementPosition(0.55f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"End Game",
		SoundType::CLICKED_RELEASE_STD
		);
	finishBtn->SetEnabled(false);
	m_elements.push_back(finishBtn);

	auto fullscreenToggleBtn = std::make_shared<ClassicButton>(
		401,
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"Toggle Fullscreen",
		SoundType::CLICKED_RELEASE_STD
		);
	fullscreenToggleBtn->SetOnClick([]() {
		auto event = ToggleFullscreenEvent();
	AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(fullscreenToggleBtn);

	auto backBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.1f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"Back",
		SoundType::CLICKED_RELEASE_STD
		);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(SceneType::MAIN_MENU)
		);
		}
	);
	m_elements.push_back(backBtn);
}

SettingsScene::SettingsScene(Vector2 resolution)
	:Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution) {
	Initialize();
}
