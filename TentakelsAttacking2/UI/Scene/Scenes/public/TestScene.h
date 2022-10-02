//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
# include "Scene.h"
# include "Table.h"

class TestScene : public Scene {
private:
	void Initialize(UIManager const& uiManager, AppContext& appContext);

protected:

public:
	TestScene(Vector2 pos, Vector2 size, Alignment alignment, UIManager const& uiManager);
	void SetActive(bool active, AppContext const& appContext) override;

};
