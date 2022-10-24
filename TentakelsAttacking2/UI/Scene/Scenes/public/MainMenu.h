//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "Scene.h"

class MainMenu : public Scene {
private:
	void Initialize(Vector2 resolution, AppContext& appContext);
public:
	MainMenu(Vector2 resolution);

	void SetActive(bool active, AppContext const& appContext) override;
};
