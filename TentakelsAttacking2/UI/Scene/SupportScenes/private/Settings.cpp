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
#include "Line.h"
#include "AppContext.h"
#include "UIEvents.hpp"
#include "GenerelEvents.hpp"

void SettingsScene::Initialize() {

	AppContext_ty appContext{ AppContext::GetInstance() };

	float           elementY{ 0.275f };
	float constexpr sliderOffset{ 0.04f };
	float constexpr elementOffset{ 0.06f };

	// title
	m_elements.push_back(std::make_shared<Title>(
		GetElementPosition(0.5f, 0.025f),
		GetElementSize(0.8f, 0.25f),
		Alignment::TOP_MID,
		m_resolution,
		false,
		appContext
		));

	// line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.5f, elementY),
		GetElementPosition(0.5f, 0.95f),
		m_resolution,
		2.0f,
		WHITE
	));

	/*// events ->
	auto eventSettings = std::make_shared<GameEventSettings>(
		1,
		GetElementPosition(0.25f, elementY),
		GetElementSize(0.25f, 0.5f),
		Alignment::TOP_MID,
		m_resolution
		);
	eventSettings->SetActive(true, appContext);
	m_elements.push_back(eventSettings);

	// fleet speed ->
	auto fleetSpeedText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		appContext.languageManager.Text("scene_settings_fleet_speed_subheadline", ":")
	);
	// lastRoundText->RenderRectangle(true);
	m_elements.push_back(fleetSpeedText);

	elementY += sliderOffset;

	auto fleetSpeed = std::make_shared<SliderAndInputLine>(
		200,
		GetElementPosition(0.75f, elementY),
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

	// last round ->
	auto lastRoundText = std::make_shared<Text>(
		GetElementPosition(0.75f, elementY),
		GetElementSize(0.4f, 0.05f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_LEFT,
		0.04f,
		appContext.languageManager.Text("scene_settings_last_round_subheadline", ":")
		);
	// lastRoundText->RenderRectangle(true);
	m_elements.push_back(lastRoundText);

	elementY += sliderOffset;

	auto lastRound = std::make_shared<SliderAndInputLine>(
		300,
		GetElementPosition(0.75f, elementY),
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

	elementY += elementOffset + 0.02f;

	// cb ->
	auto shuffleCB = std::make_shared<CheckBox>(
		350,
		GetElementPosition(0.55f, elementY),
		GetElementSize(0.0f,0.03f).y,
		Alignment::MID_LEFT,
		m_resolution,
		1
	);
	shuffleCB->SetChecked(appContext.constants.player.shuffle);
	shuffleCB->SetOnCheck([](unsigned int, bool isChecked){
		AppContext_ty appContext{AppContext::GetInstance() };
		appContext.constants.player.shuffle = isChecked;
	});
	m_elements.push_back(shuffleCB);

	auto shuffleCBText = std::make_shared<Text>(
		GetElementPosition(0.58f, elementY),
		GetElementSize(0.5f, 0.04f),
		Alignment::MID_LEFT,
		m_resolution,
		Alignment::MID_LEFT,
		0.04f,
		"shuffle player"
	);
	// shuffleCBText->RenderRectangle(true);
	m_elements.push_back(shuffleCBText);

	elementY += elementOffset;
	*/
	// btn
	/*auto finishBtn = std::make_shared<ClassicButton>(
		600,
		GetElementPosition(0.55f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		appContext.languageManager.Text("scene_settings_end_game_btn"),
		SoundType::CLICKED_RELEASE_STD
		);
	finishBtn->SetEnabled(false);
	*/
	auto continueBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.75f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		appContext.languageManager.Text("scene_settings_continue_btn"),
		SoundType::ACCEPTED
	);
	continueBtn->SetEnabled(appContext.constants.global.isGameRunning); 
	continueBtn->SetOnClick([]() {
			ResumeGameEvent const event{ };
			AppContext::GetInstance().eventManager.InvokeEvent(event);
		}
	);
	m_elements.push_back(continueBtn);

	auto backBtn = std::make_shared<ClassicButton>(
		1001,
		GetElementPosition(0.25f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		appContext.languageManager.Text("scene_settings_main_menu_btn"),
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

SettingsScene::SettingsScene(Vector2 resolution)
	:Scene{ { 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution } {
	Initialize();
}

void SettingsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}
void SettingsScene::Render(AppContext_ty_c appContext) {
	Scene::Render(appContext);
}
void SettingsScene::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	Scene::Resize(resolution, appContext);
}
