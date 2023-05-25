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

void SettingsScene::Initialize(SceneType continueScene) {

	AppContext& appContext{ AppContext::GetInstance() };

	float       elementY{ 0.3f };
	float const sliderOffset{ 0.04f };
	float const elementOffset{ 0.12f };

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
	auto settingsText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.2f),
		GetElementSize(0.3f, 0.1f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.07f,
		"Settings"
		);
	// settingsText->RenderRectangle(true);
	m_elements.push_back(settingsText);

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
	auto eventText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Volume:"
		);
	// eventText->RenderRectangle(true);
	m_elements.push_back(eventText);

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

	auto muteText = std::make_shared<Text>(
		GetElementPosition(0.566f, elementY + sliderOffset + 0.05f),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		"Mute"
		);
	// muteText->RenderRectangle(true);
	m_elements.push_back(muteText);

	elementY += elementOffset;

	// fleet speed
	auto fleetSpeedText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Fleet Speed:"
	);
	// lastRoundText->RenderRectangle(true);
	m_elements.push_back(fleetSpeedText);

	auto fleetSpeed = std::make_shared<SliderAndInputLine>(
		200,
		GetElementPosition(0.75f, elementY + sliderOffset),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		static_cast<int>(appContext.constants.fleet.minFleetSpeed),
		static_cast<int>(appContext.constants.fleet.maxFleetSpeed),
		static_cast<int>(appContext.constants.fleet.currentFleetSpeed)
	);
	fleetSpeed->SetActive(true, appContext);
	fleetSpeed->SetOnSave([](int value) {
		AppContext::GetInstance().constants.fleet.currentFleetSpeed = value;
	});
	m_elements.push_back(fleetSpeed);

	elementY += elementOffset;

	// last round
	auto lastRoundText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"ca. Last Round:"
		);
	// lastRoundText->RenderRectangle(true);
	m_elements.push_back(lastRoundText);

	auto lastRound = std::make_shared<SliderAndInputLine>(
		300,
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
		SetCurrentLastRoundEvent const event{ value };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(lastRound);

	elementY += elementOffset;

	// drop down
	auto resolutionText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		"Resolution"
		);
	// resolutionText->RenderRectangle(true);
	m_elements.push_back(resolutionText);

	elementY += 0.04f;
	auto resolutionHintText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.02f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.02f,
		"this setting is only effecting window mode"
		);
	// resolutionHintText->RenderRectangle(true);
	m_elements.push_back(resolutionHintText);

	elementY += 0.02f;
	m_dropDown = std::make_shared<DropDown>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		0.2f,
		400,
		401,
		GetStringsFromResolutionEntries()
		);
	m_dropDown->SetCurrentElementByID(GetIndexFromResolution(appContext.constants.window.current_resolution) + 1);
	m_dropDown->SetOnSave([this](unsigned int ID) {
		SetNewResolutionEvent const event{ this->m_rawResolutionEntries[ID - 1].first };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	});
	m_elements.push_back(m_dropDown);


	// btn
	auto finishBtn = std::make_shared<ClassicButton>(
		500,
		GetElementPosition(0.55f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"End Game",
		SoundType::CLICKED_RELEASE_STD
		);
	finishBtn->SetEnabled(false);
	m_dropDownBtn.first = finishBtn;

	auto fullScreenToggleBtn = std::make_shared<ClassicButton>(
		501,
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"Toggle Fullscreen",
		SoundType::CLICKED_RELEASE_STD
		);
	fullScreenToggleBtn->SetOnClick([]() {
		ToggleFullscreenEvent const event{};
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	});
	m_dropDownBtn.second = fullScreenToggleBtn;

	auto continueBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.45f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"continue",
		SoundType::ACCEPTED
	);
	if (continueScene == SceneType::NONE) { continueBtn->SetEnabled(false); }

	continueBtn->SetOnClick([continueScene]() {
		if (continueScene == SceneType::NONE) { return; }
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent(continueScene)
		);
		}
	);
	m_elements.push_back(continueBtn);

	auto backBtn = std::make_shared<ClassicButton>(
		1001,
		GetElementPosition(0.05f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		"main menu",
		SoundType::CLICKED_RELEASE_STD
		);
	backBtn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(
			SwitchSceneEvent{ SceneType::MAIN_MENU }
		);
		}
	);
	m_elements.push_back(backBtn);
}

std::vector<std::string> SettingsScene::GetStringsFromResolutionEntries() const {
	std::vector<std::string> toReturn;

	for (auto const& e : m_rawResolutionEntries) {
		toReturn.push_back(e.second);
	}

	return toReturn;
}

int SettingsScene::GetIndexFromResolution(Resolution resolution) const {
	for (int i = 0; i < m_rawResolutionEntries.size(); ++i) {
		if (m_rawResolutionEntries[i].first == resolution) {
			return i;
		}
	}
	throw std::runtime_error("resolution not existing");
}

SettingsScene::SettingsScene(Vector2 resolution, SceneType continueScene)
	:Scene{ { 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution } {
	m_rawResolutionEntries = AppContext::GetInstance().constants.window.GetAllResolutionsAsString();
	Initialize(continueScene);
}

void SettingsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	bool const folded = not m_dropDown->IsFoldedOut();
	if (folded != m_dropDownBtn.first->IsEnabled()) {
		m_dropDownBtn.first->SetEnabled(folded);
	}
	if (folded != m_dropDownBtn.second->IsEnabled()) {
		m_dropDownBtn.second->SetEnabled(folded);
	}

	if (folded) {
		m_dropDownBtn.first->CheckAndUpdate(mousePosition, appContext);
		m_dropDownBtn.second->CheckAndUpdate(mousePosition, appContext);
	}
}
void SettingsScene::Render(AppContext const& appContext) {
	m_dropDownBtn.first->Render(appContext);
	m_dropDownBtn.second->Render(appContext);
	Scene::Render(appContext);
}
void SettingsScene::Resize(Vector2 resolution, AppContext const& appContext) {
	m_dropDownBtn.first->Resize(resolution, appContext);
	m_dropDownBtn.second->Resize(resolution, appContext);
	Scene::Resize(resolution, appContext);
}
