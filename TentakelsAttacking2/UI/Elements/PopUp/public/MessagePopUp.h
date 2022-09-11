//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "PopUp.h"
#include "ClassicButton.h"

class MessagePopUp : public PopUp {
private:
	ClassicButton m_btn;

	void Initialize() override;

public:
	MessagePopUp(Vector2 pos, Vector2 size, Vector2 resolution,
		std::string const& title, std::string const& subTitle, Texture2D* btnTexture,
		Texture2D* fullBackground, Texture2D* popUpBackground, Texture2D* m_infoTexture);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render();
	void Resize(Vector2 resolution);
};
