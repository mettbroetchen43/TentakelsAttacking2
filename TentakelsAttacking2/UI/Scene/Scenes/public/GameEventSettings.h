//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include "Scene.h"

class GameEventSettings : public Scene {
private:
	void Initialize(Vector2 resoluton);

	void SetChecked(unsigned int ID, bool isCecked);

	void UpdateElements();

public:
	GameEventSettings(Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);
};
