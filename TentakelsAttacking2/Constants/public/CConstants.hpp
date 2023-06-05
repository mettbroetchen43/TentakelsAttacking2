//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include "CGlobal.hpp"
#include "CTextProcessing.hpp"
#include "CPlayer.hpp"
#include "CWorld.hpp"
#include "CFiles.hpp"
#include "CSound.hpp"
#include "CPlanet.hpp"
#include "CFleet.hpp"
#include "CWindow.h"
#include "CFight.hpp"

/**
 * contains all constants.
 */
struct Constants final {
	CGlobal global; ///< contains the global constants
	CWindow window; ///< contains the window constants
	CTextProcessing textProcessing; ///< contains the text processing constants
	CFiles files; ///< contains the file constants
	CSound sound; ///< contains the sound constants
	CPlayer player; ///< contains the player constants
	CWorld world; ///< contains the world constants
	CPlanet planet; ///< contains the planet constants
	CFleet fleet; ///< contains the fleet constants
	CFight fight; ///< contains the fight constants
};
