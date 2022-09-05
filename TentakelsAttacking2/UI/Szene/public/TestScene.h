//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "Scene.h"

class TestScene : public Scene {
private:

public:
	TestScene(Vector2 size, Vector2 pos, bool active, UIManager const& uiManager);
	~TestScene() = default;
	void InitializeSzene(UIManager const& uiManager) override;
};