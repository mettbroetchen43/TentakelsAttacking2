//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "Scene.h"

class NewGameScene : public Scene {
private:

	void Initialize(Vector2 resolution, AppContext& appContext);

public:
	NewGameScene(Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
