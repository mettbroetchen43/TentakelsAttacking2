//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"
#include "ConfigIO.h"
#include "GenerelEvents.hpp"


AppContext& AppContext::GetInstance() {
	static AppContext appContext;
	return appContext;
}

void AppContext::LoadConfig() {
	::LoadConfig();
	Validate();
	if (constants.sound.muteVolume) {
		SetMasterVolume(0.0f);
	}
	else {
		SetMasterVolume(constants.sound.masterVolume / 100);
	}
	
}
void AppContext::SaveConfig() {
	::SaveConfig();
}

void AppContext::Validate() {
	// Global
	ValidateMinMax<size_t>(constants.global.minRounds, constants.global.maxRounds,
		"Min Game Rounds", "Max Game Rounds");
	ValidateMinCurrentMax<size_t>(constants.global.minRounds, constants.global.currentRounds,
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
	ValidateLowerThan<float>(constants.sound.masterVolume, 100.0f, "Master Volume");
	ValidateGreaterThan<float>(constants.sound.masterVolume, 0.0f, "Master Volume");

	// Planet
	ValidateLowerThan<float>(constants.planet.homeworldSpacing, 1.0f, "Homeworld Spacing");
	ValidateGreaterThan<float>(constants.planet.homeworldSpacing, 0.0f, "Homeworld Spacing");

	ValidateLowerThan<float>(constants.planet.globalSpacing, 1.0f, "Global Spacing");
	ValidateGreaterThan<float>(constants.planet.globalSpacing, 0.0f, "Global Spacing");
}

void AppContext::OnEvent(Event const& event) {

	if (auto const LastRoundEvent = dynamic_cast<SetCurrentLastRoundEvent const*>(&event)) {
		constants.global.currentRounds = LastRoundEvent->GetLastRound();
		return;
	}
}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
	eventManager.AddListener(this);
}
