//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>

struct CGlobal final {
	static inline const std::string version = "v0.0.2";
	static inline const std::string copyRight = "(c) Purpur Tentakel";
	bool startingModeFullScreen = true;

	size_t minRounds = 20;
	size_t currentTargetRound = 50;
	size_t maxRounds = 100;

	size_t currentRound = 0;

	size_t FPS = 60;
};
