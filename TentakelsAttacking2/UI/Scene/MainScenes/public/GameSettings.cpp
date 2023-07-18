//
// Purpur Tentakel
// 18.07.2023
//

#include "GameSettings.h"
#include "Text.h"
#include "GameEventSettings.h"
#include "SliderAndInputLine.h"
#include "GenerelEvents.hpp"
#include "CheckBox.h"
#include "ClassicButton.h"

void GameSettingsScene::Initialize() {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	// headline
	auto settingsText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.2f),
		GetElementSize(0.3f, 0.1f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.07f,
		"Game Settings"
	);
	m_elements.push_back(settingsText);

	auto finishBtn = std::make_shared<ClassicButton>(
		999,
		GetElementPosition(0.25f, 0.81f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_MID,
		m_resolution,
		appContext.languageManager.Text("scene_settings_end_game_btn"),
		SoundType::CLICKED_RELEASE_STD
	);
	finishBtn->SetEnabled(false);
	m_elements.push_back(finishBtn);

	// constants
	int                 id     { 1       };
	float               y      { 0.32f   };
	float     constexpr lx     { 0.05f   };
	float     constexpr rx     { 0.55f   };
	float     constexpr width  { 0.40f   };
	float     constexpr heightS{ 0.025f  };
	float     constexpr height { 0.05f   };
	float     constexpr offset { height  + 0.005f };
	float     constexpr offsetS{ heightS + 0.005f };
	[[maybe_unused]]
	float     constexpr rxwoS  { rx + heightS     };
	float     constexpr rxwo   { rx + height      };
	[[maybe_unused]]
	float     constexpr lxwoS  { lx + heightS     };
	[[maybe_unused]]
	float     constexpr lxwo   { lx + height      };
	Alignment constexpr a      { Alignment::MID_LEFT };

	// increase
	auto const incFIDS{[&](){
		++id;
	}};
	auto const incFIDB{[&](){
		id += 100;
	}};
	auto const incPosS{[&](){
		y += offsetS;
	}};
	auto const incPosB{[&](){
		y += offset;
	}};

	// first
	auto eventSettings = std::make_shared<GameEventSettings>(
		id,
		GetElementPosition(0.25f, y),
		GetElementSize(width, 0.5f),
		Alignment::TOP_MID,
		m_resolution
	);
	eventSettings->SetActive(true, appContext);
	m_elements.push_back(eventSettings);

	incFIDB(); // big because event settings could increase

	auto fleetSpeedText = std::make_shared<Text>(
		GetElementPosition(rx, y),
		GetElementSize(width, height),
		a,
		m_resolution,
		a,
		height,
		appContext.languageManager.Text("scene_settings_fleet_speed_subheadline", ":")
	);
	m_elements.push_back(fleetSpeedText);

	incPosB(); 

	auto fleetSpeed = std::make_shared<SliderAndInputLine>(
		id,
		GetElementPosition(rx, y),
		GetElementSize(width, height),
		a,
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

	incFIDS(); // two because slider and input line needs two ids
	incFIDS();
	incPosB();

	// last round ->
	auto lastRoundText = std::make_shared<Text>(
		GetElementPosition(rx, y),
		GetElementSize(width, height),
		a,
		m_resolution,
		a,
		height,
		appContext.languageManager.Text("scene_settings_last_round_subheadline", ":")
	);
	m_elements.push_back(lastRoundText);

	incPosB();

	auto lastRound = std::make_shared<SliderAndInputLine>(
		id,
		GetElementPosition(rx, y),
		GetElementSize(width, height),
		a,
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

	incFIDS(); // two because slider and input line needs two ids
	incFIDS();
	incPosB();
	incPosS();

	auto playerShuffleCB = std::make_shared<CheckBox>(
		id,
		GetElementPosition(rx, y),
		GetElementSize(0.0f,height).y,
		Alignment::MID_LEFT,
		m_resolution,
		1
	);
	playerShuffleCB->SetChecked(appContext.constants.player.shuffle);
	playerShuffleCB->SetOnCheck([](unsigned int, bool isChecked){
		AppContext_ty appContext{AppContext::GetInstance() };
		appContext.constants.player.shuffle = isChecked;
	});
	m_elements.push_back(playerShuffleCB);

	incFIDS();

	auto shuffleCBText = std::make_shared<Text>(
		GetElementPosition(rxwo, y),
		GetElementSize(width, height),
		a,
		m_resolution,
		a,
		height,
		"shuffle player"
	);
	m_elements.push_back(shuffleCBText);
}

GameSettingsScene::GameSettingsScene(Vector2 resolution)
	: SettingsScene { resolution } {
	
	Initialize();
}
