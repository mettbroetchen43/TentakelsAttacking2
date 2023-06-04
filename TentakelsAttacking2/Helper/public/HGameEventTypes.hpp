//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include <array>

/**
 * provides the Types of all game events.
 */
enum class HGameEventType {
	GLOBAL,
	PIRATES,
	REVOLTS,
	RENEGADE_SHIPS,
	BLACK_HOLE,
	SUPERNOVA,
	ENGINE_PROBLEM,
};

using EventTypeArray = std::array<HGameEventType, 6>; ///< type of the settable events
constexpr EventTypeArray settableGameEventTypes{ ///< contains the settable events
	HGameEventType::PIRATES,
	HGameEventType::REVOLTS,
	HGameEventType::RENEGADE_SHIPS,
	HGameEventType::BLACK_HOLE,
	HGameEventType::SUPERNOVA,
	HGameEventType::ENGINE_PROBLEM,
};
