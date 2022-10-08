//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "PopUp.h"
#include "ClassicButton.h"

class MessagePopUp : public PopUp {
private:
	void Initialize(Vector2 resolution);

public:
	MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture);
};