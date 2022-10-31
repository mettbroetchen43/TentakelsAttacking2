//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"
#include "ConfigIO.h"


AppContext& AppContext::GetInstance() {
	static AppContext appContext;
	return appContext;
}

void AppContext::LoadConfig() {
	::LoadConfig();
	Validate();
	SetMasterVolume(constants.sound.masterVolume / 100);
}
void AppContext::SaveConfig() {
	::SaveConfig();
}

void AppContext::Validate() {
	// Player
	ValidateMinMax<size_t>(constants.player.minPlayerCount, constants.player.maxPlayerCount,
		"minPlayerCount", "maxPlayerCount");

	// World
	ValidateMinMax<size_t>(constants.world.minPlanetCount, constants.world.maxPlanetCount,
		"minPlanetCount", "maxPlanetCount");
	ValidateMinCurrentMax<size_t>(constants.world.minPlanetCount, constants.world.currentPlanetCount,
		constants.world.maxPlanetCount);

	ValidateMinMax<size_t>(constants.world.minDiemnsionX, constants.world.maxDiemnsionX,
		"minDiemnsionX", "maxDiemnsionX");
	ValidateMinCurrentMax<size_t>(constants.world.minDiemnsionX, constants.world.currentDimensionX,
		constants.world.maxDiemnsionX);

	ValidateMinMax<size_t>(constants.world.minDiemnsionY, constants.world.maxDiemnsionY,
		"minDiemnsionY", "maxDiemnsionY");
	ValidateMinCurrentMax<size_t>(constants.world.minDiemnsionY, constants.world.currentDimensionY,
		constants.world.maxDiemnsionY);

	// Sound
	ValidateLowerThan<float>(constants.sound.masterVolume, 100.0f, "MasterVolume");
	ValidateGreaterThan<float>(constants.sound.masterVolume, 0.0f, "MasterVolume");
}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
}
