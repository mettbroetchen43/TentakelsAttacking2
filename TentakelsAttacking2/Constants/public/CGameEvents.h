//
// Purpur Tentakel
// 12.07.2023
//

#pragma once
#include "HGameEventTypes.hpp"
#include <array>

struct CGameEvents {
	HGameEventType events{ 0b11111111 };

	using EventTypeArray = std::array<HGameEventType, 6>; ///< type of the settable events
	static constexpr EventTypeArray settableGameEventTypes{ ///< contains the settable events
		HGameEventType::PIRATES,
		HGameEventType::REVOLTS,
		HGameEventType::RENEGADE_SHIPS,
		HGameEventType::BLACK_HOLE,
		HGameEventType::SUPERNOVA,
		HGameEventType::ENGINE_PROBLEM,
	};

	void FlagType(HGameEventType const type, bool const active);
	[[nodiscard]] bool IsFlag(HGameEventType const type) const;
};
