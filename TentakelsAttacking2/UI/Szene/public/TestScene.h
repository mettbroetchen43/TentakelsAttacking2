//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "BaseMainScene.h"

class TestScene : public BaseMainScene {
private:

public:
	TestScene(Vector2 pos, Vector2 size, bool active, UIManager const& uiManager);
	~TestScene() = default;
	void InitializeSzene(UIManager const& uiManager);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Test();
};