//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

struct CWorld final {
	size_t minPlanetCount = 20;
	size_t currentPlanetCount = 50;
	size_t maxPlanetCount = 100;
	size_t showPlanetCount = 25;

	int minDiemnsionX = 60;
	int currentDimensionX = 150;
	int maxDiemnsionX = 300;

	int minDiemnsionY = 20;
	int currentDimensionY = 80;
	int maxDiemnsionY = 160;

	int showDimensionX = 200;
	int showDimensionY = 150;
};