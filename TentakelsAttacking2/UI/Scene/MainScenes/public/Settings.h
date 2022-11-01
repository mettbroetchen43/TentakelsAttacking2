//
// Purpur Tentakel
// 01.11.2022
//

#pragma once
#include "Scene.h"

class SettingsScene : public Scene {
private:
	void Initialize(Vector2 resolution);

public:
	SettingsScene(Vector2 resolution);
};