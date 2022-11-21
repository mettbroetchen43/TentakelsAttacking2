//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "PopUp.h"
#include <functional>

class ValidatePopUp : public PopUp {
private:
	std::function<void(bool)> m_callback = [](bool) {};

	void Initialize();

	void Close();
public:
	ValidatePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture, std::function<void(bool)> callback);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
};