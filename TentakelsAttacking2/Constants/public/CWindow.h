//
// Purpur Tentakel
// 10.12.2022
//

#pragma once
#include "HResolution.hpp"
#include <vector>
#include <string>
#include <array>


struct CWindow final {
	Resolution current_resolution{ Resolution::LAST }; ///< contains the current resolution in window mode (override by contig)

	bool startingModeFullScreen{ true }; ///< defines if the game is starting in fullscreen mode (override by config)
	bool isCurrentFullScreenMode{ true }; ///< defines if the game is currently in fullscreen mode (overritten by config)

	size_t FPS{ 60 }; ///< contains the target FPS (override by config)

	/**
	 * checks if the provided resolution would fit onto the screen
	 */
	[[nodiscard]] bool IsPossibleResolution(Resolution toProove);
	/**
	 * returns all resolutions as pair of resolution and string
	 */
	[[nodiscard]] std::vector<std::pair<Resolution, std::string>> GetAllResolutionsAsString();
	/** 
	 * returns a string for the provided resolution.
	 */
	[[nodiscard]] std::string GetStringFromResolution(Resolution resolution);
	/**
	 * returns the provided resolution as int.
	 */
	[[nodiscard]] std::pair<int, int> GetIntFromResolution(Resolution resolution);
};
