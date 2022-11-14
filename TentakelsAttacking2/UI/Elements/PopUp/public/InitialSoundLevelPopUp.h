//
// Purpur Tentakel
// 14.11.2022
//

#pragma once
#include "PopUp.h"

class InitialSoundLevelPopUp : public PopUp {
private:
	void Initialize(Vector2 resolution);

public:
	InitialSoundLevelPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle);
};