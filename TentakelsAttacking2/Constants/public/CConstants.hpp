//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include "CGlobal.hpp"
#include "CTextProcecing.hpp"
#include "CPlayer.hpp"
#include "CWorld.hpp"
#include "CFiles.hpp"
#include "CSound.hpp"
#include "CPlanet.hpp"
#include "CWindow.h"

/**
 * contains all constants.
 */
struct Constants final {
	CGlobal global{ }; ///< contains the global constants
	CTextProcecing textProcessing{ }; ///< contains the text processing constants
	CPlayer player{ }; ///< contains the player constants
	CWorld world{ }; ///< contains the world constants
	CFiles files{ }; ///< contains the file constants
	CSound sound{ }; ///< contains the sound constants
	CPlanet planet{ }; ///< contains the planet constants
	CWindow window{ }; ///< contains the window constants
};