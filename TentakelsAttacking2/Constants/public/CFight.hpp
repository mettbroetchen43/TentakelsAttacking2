//
// Purpur Tentakel
// 04.06.2023
//

#pragma once

struct CFight final {
	static inline int const configEntryCount{ 1 }; ///< config load checks if the count is idetical to the loaded entry count
	float hitChance{ 0.3f }; ///< gets overwritten by config
};