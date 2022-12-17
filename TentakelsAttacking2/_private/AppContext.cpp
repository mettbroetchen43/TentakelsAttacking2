//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"
#include "ConfigIO.h"
#include "GenerelEvents.hpp"
#include "UIEvents.hpp"
#include "HPrint.h"


AppContext& AppContext::GetInstance() {
	static AppContext appContext;
	return appContext;
}

void AppContext::LoadConfig() {
	::LoadConfig();
	if (constants.sound.muteVolume) {
		SetMasterVolume(0.0f);
	}
	else {
		SetMasterVolume(constants.sound.masterVolume / 100);
	}
	
	auto event = SetTargetFPSEvent(constants.window.FPS);
	eventManager.InvokeEvent(event);

}
void AppContext::SaveConfig() {
	::SaveConfig();
}

void AppContext::ValidateConfig() {
	// Global
	ValidateMinMax<size_t>(constants.global.minRounds, constants.global.maxRounds,
		"Min Game Rounds", "Max Game Rounds");
	ValidateMinCurrentMax<size_t>(constants.global.minRounds, constants.global.currentTargetRound,
		constants.global.maxRounds);

	// Player
	ValidateMinMax<size_t>(constants.player.minPlayerCount, constants.player.maxPlayerCount,
		"Min Player Count", "Max Player Count");

	// World
	ValidateMinMax<size_t>(constants.world.minPlanetCount, constants.world.maxPlanetCount,
		"Min Planet Count", "Max Planet Count");
	ValidateMinCurrentMax<size_t>(constants.world.minPlanetCount, constants.world.currentPlanetCount,
		constants.world.maxPlanetCount);

	ValidateMinMax<int>(constants.world.minDiemnsionX, constants.world.maxDiemnsionX,
		"Min World Width", "Max World Width");
	ValidateMinCurrentMax<int>(constants.world.minDiemnsionX, constants.world.currentDimensionX,
		constants.world.maxDiemnsionX);

	ValidateMinMax<int>(constants.world.minDiemnsionY, constants.world.maxDiemnsionY,
		"Min World Height", "Max World Height");
	ValidateMinCurrentMax<int>(constants.world.minDiemnsionY, constants.world.currentDimensionY,
		constants.world.maxDiemnsionY);

	// Sound
	ValidateLowerEqual<float>(constants.sound.masterVolume, 100.0f, "Master Volume");
	ValidateGreaterEqual<float>(constants.sound.masterVolume, 0.0f, "Master Volume");

	// Planet
	ValidateLowerEqual<float>(constants.planet.homeworldSpacing, 1.0f, "Homeworld Spacing");
	ValidateGreaterEqual<float>(constants.planet.homeworldSpacing, 0.0f, "Homeworld Spacing");

	ValidateLowerEqual<float>(constants.planet.globalSpacing, 1.0f, "Global Spacing");
	ValidateGreaterEqual<float>(constants.planet.globalSpacing, 0.0f, "Global Spacing");

	Print("Contig validated");
}

void AppContext::OnEvent(Event const& event) {

	if (auto const LastRoundEvent = dynamic_cast<SetCurrentLastRoundEvent const*>(&event)) {
		constants.global.currentTargetRound = LastRoundEvent->GetLastRound();
		return;
	}
}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
	eventManager.AddListener(this);

	Print("AppContext initialized");
}
