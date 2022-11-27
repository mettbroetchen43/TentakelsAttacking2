//
// Purpur Tentakel
// 28.10.2022
//

#pragma once

/**
 * conatins all sound constants
 */
struct CSound final {
	bool muteVolume = false; ///< contains if the game is muted (override by config, true == mute)
	float masterVolume = 50.0f; ///< contains the current master volume (override by config)
};
