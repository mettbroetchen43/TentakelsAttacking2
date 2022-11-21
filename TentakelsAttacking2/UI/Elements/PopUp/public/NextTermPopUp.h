//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "PopUp.h"

class NextTermPopUp : public PopUp {
private:
	void Initialize();

	void Close();
public:
	NextTermPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture);
};