//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "SoundManager.h"
#include "EventManager.h"
#include "AssetManager.h"
#include <string>

struct AppContext {
	SoundManager soundManager;
	AssetManager assetManager;
	EventManager eventManager;

	[[nodiscard]] static AppContext& GetInstance();
	[[nodiscard]] std::string const& Version() const;
	[[nodiscard]] std::string const& CopyRight() const;

private:
	AppContext();
	std::string m_version = "v0.0.0";
	std::string m_copyRight = "(c) Purpur Tentakel";
};
