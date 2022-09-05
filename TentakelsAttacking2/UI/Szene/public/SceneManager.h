//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "SceneType.h"
#include <unordered_map>
#include <memory>

class UIManager;
class Focus;
class Scene;
struct AppContext;
struct Vector2;

class SceneManager {
private:
	UIManager* m_uiManager;
	std::unordered_map<SceneType, std::shared_ptr<Scene>> m_scenes;
	std::shared_ptr<Scene> m_currentScene;

	void InitializeScenes();

public:
	SceneManager(UIManager* uiManager);

	void SwitchScene(SceneType sceneType);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render();
	void Resize(Vector2 resolution);
};

