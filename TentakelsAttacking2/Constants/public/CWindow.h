//
// Purpur Tentakel
// 10.12.2022
//

#pragma once

enum class Resolution {
	UHD,
	FULL_HD,
	HD,
};

struct CWindow {
	Resolution current_resolution = Resolution::FULL_HD; ///< contains the current resolution in window mode (override by contig)
	
	bool startingModeFullScreen = true; ///< defines if the game is starting in fullscreen mode (override by config)
	bool isCurrentFullScreenMode = true; ///< defines if the game is currently in fullscreen mode (overritten by config)
	
	size_t FPS = 60; ///< contains the target FPS (override by config)
};
