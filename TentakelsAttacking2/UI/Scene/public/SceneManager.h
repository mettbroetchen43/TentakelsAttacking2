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

class SceneManager : public EventListener {
private:
	UIManager* m_uiManager;
	PopUpManager m_popUpManager;

	std::unordered_map<SceneType, std::shared_ptr<Scene>> m_scenes;
	std::shared_ptr<Scene> m_currentScene;

	std::vector<std::shared_ptr<PopUp>> m_popUps;

	void InitializeScenes();
	/*void NewMessagePopUp(std::string const& title, std::string const& subTitle);
	template<typename popUpType, typename eventType>
	void NewTableCellPopUp(eventType const* event) {
		AppContext& appContext = AppContext::GetInstance();
		auto event = NewFocusLayerEvent();
		appContext.eventManager.InvokeEvent(event);

		auto popUp = std::make_shared<popUpType>(
			Vector2(0.5f, 0.5f),
			Vector2(0.7f, 0.7f),
			Alignment::MID_MID,
			*m_uiManager->GetResolution(),
			event->GetTitle(),
			AssetType::LOGO,
			event->GetCell()
			);
		m_popUps.push_back(popUp);
	}
	void DeleteLastPopUp();*/

public:
	SceneManager(UIManager* uiManager);

	void SwitchScene(SceneType sceneType, AppContext const& appContext);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);

	void OnEvent(Event const& event);

};

