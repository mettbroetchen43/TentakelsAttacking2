//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "Scene.h"
#include <functional>

struct AppContext;
enum class SceneType;
#define SCENE_LENGTH 5.0

class LogoScene : public Scene {
private:
	SceneType m_nextScene;
	double m_time;

	void Initialize(Vector2 resolution);

public:
	LogoScene(Vector2 pos, Vector2 size, Alignment alignment,
		SceneType nextScene, Vector2 resolution);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetActive(bool active, AppContext const& appContext) override;
};
