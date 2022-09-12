//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "SceneType.h"
#include "EventListener.h"
#include <unordered_map>
#include <memory>
#include <vector>

class UIManager;
class Focus;
class Focusable;
class Scene;
class PopUp;
struct AppContext;
struct Vector2;

class SceneManager : public EventListener {
private:
	UIManager* m_uiManager;
	std::unordered_map<SceneType, std::shared_ptr<Scene>> m_scenes;
	std::shared_ptr<Scene> m_currentScene;
	
	std::vector<std::shared_ptr<PopUp>> m_popUp;


	void InitializeScenes();
	void NewMessagePopUp(std::string const& title, std::string const& subTitle);
	void DeleteLastPopUp();

public:
	SceneManager(UIManager* uiManager);

	void SwitchScene(SceneType sceneType);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution);

	void OnEvent(Event const& event);
};

