//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "SceneType.hpp"
#include "PopUp.h"
#include "PopUpManager.h"
#include <unordered_map>
#include <memory>
#include <vector>

class Focus;
class Focusable;
class Scene;
struct AppContext;
struct Vector2;
class UIManager;

class SceneManager final : public EventListener {
private:
	UIManager* m_uiManager;
	PopUpManager m_popUpManager;

	SceneType m_currentSceneType = SceneType::NONE;
	SceneType m_nextSceneType = SceneType::NONE;
	std::shared_ptr<Scene> m_currentScene;

	void InitializeNewScene(SceneType sceneType);
	void SwitchScene(AppContext const& appContext);

public:
	SceneManager(UIManager* uiManager);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);

	void OnEvent(Event const& event);

};

