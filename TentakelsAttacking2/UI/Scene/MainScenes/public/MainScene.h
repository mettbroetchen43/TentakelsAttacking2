//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "Scene.h"
#include "SceneType.h"
#include "EventListener.hpp"
#include "HPlayerData.hpp"
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
		CLEAR,
	};

	std::shared_ptr<GalaxyScene> m_galaxy;
	// std::shared_ptr<GalaxyScene> m_planetTable;
	// std::shared_ptr<GalaxyScene> m_fleetTable;
	std::shared_ptr<ClassicButton> m_nextBtn;
	std::shared_ptr<Text> m_currentPlayerName;
	std::shared_ptr<Text> m_nextPlayerName;
	std::shared_ptr<Text> m_currentRound;
	std::shared_ptr<Text> m_currentTargetRound;
	PlayerData m_currentPlayer, m_nextPlayer;

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