//
// Purpur Tentakel
// 12.07.2023
//

#pragma once
#include "HGameEventTypes.hpp"
#include <array>

/**
 * contains the constants for the game events.
 */
struct CGameEvents {
	HGameEventType events{ 0b11111111 }; ///< contains the bismask for the events --> get overwritten by config

	using EventTypeArray = std::array<HGameEventType, 6>; ///< type of the settable events
	static constexpr EventTypeArray settableGameEventTypes{ ///< contains the settable events
		HGameEventType::PIRATES,
		HGameEventType::REVOLTS,
		HGameEventType::RENEGADE_SHIPS,
		HGameEventType::BLACK_HOLE,
		HGameEventType::SUPERNOVA,
		HGameEventType::ENGINE_PROBLEM,
	};

	/**
	 * sets the bitflag for a specific game event type.
	 */
	void SetFlag(HGameEventType const type, bool const active);
	/**
	 * return if the flag for a specific game event type is set.
	 */
	[[nodiscard]] bool IsFlag(HGameEventType const type) const;
};
