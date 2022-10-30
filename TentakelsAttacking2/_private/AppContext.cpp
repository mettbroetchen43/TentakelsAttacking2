//
// Purpur Tentakel
// 04.09.2022
//

#include "AppContext.h"
#include "ConfigIO.h"
#include "UIEvents.hpp"

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
	ValidatePlayer();
}
void AppContext::ValidatePlayer() {
	if (constants.player.minPlayerCount >= constants.player.maxPlayerCount) {
		constants.player.maxPlayerCount = constants.player.minPlayerCount + 1;
		auto event = ShowMessagePopUpEvent(
			"Invalid Config",
			"minPlayerCount >= maxPlayerCount\nset maxPlayerCount to "
				+ std::to_string(constants.player.maxPlayerCount)
		);
		eventManager.InvokeEvent(event);
	}
}

AppContext::AppContext() {
	eventManager.AddListener(&soundManager);
	eventManager.AddListener(&playerCollection);
}
