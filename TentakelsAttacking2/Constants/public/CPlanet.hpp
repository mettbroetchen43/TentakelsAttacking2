//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

struct CPlanet final {
	size_t maxShips = 200;
	size_t statringHumanShipsMultiplicator = 10; // multiply with production
	size_t statringGlobalShipsMultiplicator = 5; // multiply with production

	size_t homeworldProduction = 10;
	size_t minProduction = 3;
	size_t maxProduction = 7;

	float homeworldSpacing = 0.15f;
	float globalSpacing = 0.02f;
};
