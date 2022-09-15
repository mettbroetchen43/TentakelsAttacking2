//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "Scene.h"
#include "Text.h"
#include <functional>

struct AppContext;
enum class SceneType;
#define SCENE_LENGTH 10.0

class LogoScene : public Scene {
private:
	SceneType m_nextScene;
	double m_time;
	Texture2D* m_logo;

	void Initialize(UIManager const& uiManager);

public:
	LogoScene(Vector2 pos, Vector2 size, SceneType nextScene, UIManager const& uiManager);
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetActive(bool active, AppContext const& appContext) override;
};
