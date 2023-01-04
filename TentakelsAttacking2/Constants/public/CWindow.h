//
// Purpur Tentakel
// 10.12.2022
//

#pragma once
#include "HResolution.hpp"
#include <vector>
#include <string>
#include <array>



struct CWindow {
	Resolution current_resolution = Resolution::LAST; ///< contains the current resolution in window mode (override by contig)
	
	bool startingModeFullScreen = true; ///< defines if the game is starting in fullscreen mode (override by config)
	bool isCurrentFullScreenMode = true; ///< defines if the game is currently in fullscreen mode (overritten by config)
	
	size_t FPS = 60; ///< contains the target FPS (override by config)

	[[nodiscard]] bool IsPossibleResolution(Resolution toProove);
	[[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString ( );
	[[nodiscard]] std::string GetStringFromResolution ( Resolution resolution );
	[[nodiscard]] std::array<int, 2> GetIntFromResolution ( Resolution resolution );
};

