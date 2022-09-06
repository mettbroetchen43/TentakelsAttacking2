//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "Scene.h"

class BaseMainScene : public Scene {
protected:
	void InitializeSzene(UIManager const& uiManager) override;

public:
	using Scene::Scene;
};