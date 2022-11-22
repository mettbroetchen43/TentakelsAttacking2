//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "PopUp.h"
#include "ClassicButton.h"
#include <functional>

class MessagePopUp final : public PopUp {
private:
	std::function<void()> m_callback = []() {};

	void Initialize(Vector2 resolution);

public:
	MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture, std::function<void()> callback);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};