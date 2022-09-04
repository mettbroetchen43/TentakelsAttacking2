//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "SoundManager.h"
#include "EventManager.h"
#include "AssetManager.h"

struct AppContext {
	SoundManager soundManager;
	AssetManager assetManager;
	EventManager eventManager;

	[[nodiscard]] static AppContext& GetInstance();

private:
	AppContext();

};
