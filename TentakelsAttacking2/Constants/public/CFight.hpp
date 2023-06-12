//
// Purpur Tentakel
// 04.06.2023
//

#pragma once

struct CFight final {
	static inline int const configEntryCount{ 2 }; ///< config load checks if the count is idetical to the loaded entry count
	float hitChance{ 0.3f }; ///< contains the change a single ship will hit. gets overwritten by config
	int fleetFightRange{ 3 }; ///< contains the range 2 fleets will fight. get ovberwritten by config.
};