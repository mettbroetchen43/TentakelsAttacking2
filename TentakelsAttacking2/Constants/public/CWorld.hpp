//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

struct CWorld final {
	size_t minPlanetCount = 20;
	size_t currentPlanetCount = 50;
	size_t maxPlanetCount = 100;

	size_t minDiemnsionX = 60;
	size_t currentDimensionX = 150;
	size_t maxDiemnsionX = 300;

	size_t minDiemnsionY = 20;
	size_t currentDimensionY = 80;
	size_t maxDiemnsionY = 160;

	size_t showPlanetCount = 25;
	size_t showDimensionX = 200;
	size_t showDimensionY = 150;
};