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
		"minPlayerCount >= maxPlayerCount\nset maxPlayerCount to ");

	// Sound
	ValidateSound();
}
void AppContext::ValidateSound() {
	auto& volume = constants.sound.masterVolume;

	if (volume < 0.0f) {
		volume = 0.0f;
		auto event = ShowMessagePopUpEvent("Invalid Config",
			"masterVolume < 0.0\nset Volume to " + std::to_string(volume)
		);
		eventManager.InvokeEvent(event);
	}
	else if (volume > 100.0f) {
		volume = 100.0f;
		auto event = ShowMessagePopUpEvent("Invalid Config",
			"masterVolume > 100.0\nset Volume to " + std::to_string(volume)
		);
		eventManager.InvokeEvent(event);
	}

}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
}
