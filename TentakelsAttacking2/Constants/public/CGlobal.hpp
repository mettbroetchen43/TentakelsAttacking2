//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>

/**
 * contains the global constants
 */
struct CGlobal final {
	static inline const std::string version = "v0.0.3"; ///< current version string
	static inline const std::string copyRight = "(c) Purpur Tentakel"; ///< copy right string
	

	size_t minRounds = 20; ///< defines the min of rounds the player can set (override by config)
	size_t currentTargetRound = 50; ///< contains the current target round that the player has set (override by config)
	size_t maxRounds = 100; ///< defines the max of rounds the player can set (override by config)

	size_t currentRound = 0; ///< contains the current round of the game
};
