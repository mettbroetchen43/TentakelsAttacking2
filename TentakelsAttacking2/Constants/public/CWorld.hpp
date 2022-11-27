//
// Purpur Tentakel
// 27.10.2022
//

#pragma once

/**
 * contains all world constants
 */
struct CWorld final {
	size_t minPlanetCount = 20; ///< defines the min count of planet the unser can set (override by config)
	size_t currentPlanetCount = 50; ///< contains the current count of planets the player has set (override by config)
	size_t maxPlanetCount = 100; ///< defines the max count of planet the unser can set (override by config)
	size_t showPlanetCount = 25; ///< defines the count of planet that are displayed in the show galaxy(override by config)

	int minDiemnsionX = 60; ///< defines the min width of the galaxy the unser can set (override by config)
	int currentDimensionX = 150; ///< contains the current width of the galaxy the player has set (override by config)
	int maxDiemnsionX = 300; ///< defines the max width of the galaxy the unser can set (override by config)

	int minDiemnsionY = 20; ///< defines the min height of the galaxy the unser can set (override by config)
	int currentDimensionY = 80; ///< contains the current height of the galaxy the player has set (override by config)
	int maxDiemnsionY = 160; ///< defines the max height of the galaxy the unser can set (override by config)

	int showDimensionX = 200; ///< defines the width of the show galaxy(override by config)
	int showDimensionY = 150; ///< defines the height of the show galaxy(override by config)
};