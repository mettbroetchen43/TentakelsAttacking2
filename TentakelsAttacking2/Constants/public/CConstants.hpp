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

struct Constants final {
	CGlobal global;
	CTextProcecing textProcecing;
	CPlayer player;
	CWorld world;
	CFiles files;
	CSound sound;
	CPlanet planet;
};