//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "PopUp.h"
#include "ClassicButton.h"

class MessagePopUp final : public PopUp {
private:
	void Initialize(Vector2 resolution);

public:
	MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};