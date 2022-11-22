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

/**
 * contains all constants.
 */
struct Constants final {
	CGlobal global; ///< contains the golbal constats
	CTextProcecing textProcecing; ///< contains the text procecing constants
	CPlayer player; ///< contains the player constants
	CWorld world; ///< contains the world constants
	CFiles files; ///< contains the file constants
	CSound sound; ///< contains the sound constants
	CPlanet planet; ///< contains the planet constants
};