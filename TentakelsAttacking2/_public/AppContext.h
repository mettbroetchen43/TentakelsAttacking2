//
// Purpur Tentakel
// 25.08.2022
//

#pragma once
#include "HSoundManager.h"
#include "EventManager.hpp"
#include "HAssetManager.h"
#include "HPlayerCollection.h"
#include "HColors.h"
#include "CConstants.hpp"
#include <string>

struct AppContext {
public:
	SoundManager soundManager;
	AssetManager assetManager;
	EventManager eventManager;
	PlayerCollection playerCollection;
	Colors colors;
	Constants constants;
	

	[[nodiscard]] static AppContext& GetInstance();
	[[nodiscard]] std::string const& Version() const;
	[[nodiscard]] std::string const& CopyRight() const;
	[[nodiscard]] bool IsMaximizedStartingWindow() const;

private:

#ifdef _DEBUG
	bool m_startingMaximizedWindow = false;
#else
	bool m_startingMaximizedWindow = true;
#endif // _DEBUG

	AppContext();
	std::string m_version = "v0.0.0";
	std::string m_copyRight = "(c) Purpur Tentakel";
};
