//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

/**
 * contains the player constants
 */
struct CPlayer final {
	size_t minPlayerCount{ 2 }; ///< defines the min player needed for a game (override by config)
	size_t maxPlayerCount{ 7 }; ///< defines the max player slots available for one game (override by config)
};