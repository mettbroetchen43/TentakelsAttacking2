//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include <array>

enum class GameEventType {
	GLOBAL,
	PIRATES,
	REVOLTS,
	RENEGADE_SHIPS,
	BLACK_HOLE,
	SUPERNOVA,
	ENGINE_PROBLEM,
};

using EventTypeArray = std::array<GameEventType, 6>;
constexpr EventTypeArray settableGameEventTypes = {
	GameEventType::PIRATES,
	GameEventType::REVOLTS,
	GameEventType::RENEGADE_SHIPS,
	GameEventType::BLACK_HOLE,
	GameEventType::SUPERNOVA,
	GameEventType::ENGINE_PROBLEM,
};
