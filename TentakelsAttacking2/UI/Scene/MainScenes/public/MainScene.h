//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "EventListener.hpp"
#include <memory>

class GalaxyScene;
class ClassicButton;
class Text;

class MainScene : public Scene, public EventListener {
private:
	enum class MainSceneType {
		GALAXY,
		PLANET_TABLE,
		FLEET_TABLE,
	};

	std::shared_ptr<GalaxyScene> m_galaxy;
	// std::shared_ptr<GalaxyScene> m_planetTable;
	// std::shared_ptr<GalaxyScene> m_fleetTable;
	std::shared_ptr<ClassicButton> m_nextBtn;
	std::shared_ptr<Text> m_currentPlayerText;
	std::shared_ptr<Text> m_nextPlayerText;
	unsigned int m_currentPlayerID, m_nextPlayerID;

	void Initialize();
	void InitialzeGalaxy();

	void NextTerm();
	void NextRound();

	void SetPlayerText();

	void Switch(MainSceneType sceneType);

public:
	MainScene(Vector2 resolution);
	~MainScene();

	void OnEvent(Event const& event) override;
};