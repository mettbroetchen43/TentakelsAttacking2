//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "Scene.h"

class MainMenu : public Scene {
private:
	void Initialize(UIManager const& uiManager, AppContext& appContext);
public:
	MainMenu(Vector2 pos, Vector2 size, Alignment alignment, UIManager const& uiManager);
	void SetActive(bool active, AppContext const& appContext) override;
};
