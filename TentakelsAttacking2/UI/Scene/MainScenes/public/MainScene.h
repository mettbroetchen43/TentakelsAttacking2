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

/**
 * provides the main scene.
 */
class MainScene : public Scene, public EventListener {
private:
	enum class MainSceneType { ///< provides the types for the support scenes in that scene
		GALAXY,
		PLANET_TABLE,
		FLEET_TABLE,
		CLEAR,
	};

	std::shared_ptr<GalaxyScene> m_galaxy; ///< contains the current ui galaxy
	// std::shared_ptr<GalaxyScene> m_planetTable; 
	// std::shared_ptr<GalaxyScene> m_fleetTable;
	std::shared_ptr<ClassicButton> m_nextBtn; ///< contains the next term / round button
	std::shared_ptr<Text> m_currentPlayerName; ///< contains the current player name
	std::shared_ptr<Text> m_nextPlayerName; ///< contains the next player name
	std::shared_ptr<Text> m_currentRound;  ///< contains the current round count
	std::shared_ptr<Text> m_currentTargetRound;  ///< contains the current taregt round count
	PlayerData m_currentPlayer; ///< contains the data of the current player
	PlayerData m_nextPlayer; ///< contains the data of the next player

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();
	/**
	 * removes old ui galaxy if one exists.
	 * initialzes a new ui galaxy.
	 */
	void InitialzeGalaxy();

	/**
	 * swtitches the support scene to clear.
	 * updates player text and initializes a new galaxy.
	 * generates an popup.
	 */
	void NextTerm();
	/**
	 * updates player text and rouns.
	 * initialzes a new galaxy.
	 * generates an popup.
	 */
	void NextRound();

	/**
	 * updates player text and color.
	 */
	void SetPlayerText();

	/**
	 * sets all scene inactive.
	 * sets the provided scene active.
	 */
	void Switch(MainSceneType sceneType);

public:
	/**
	 * ctor.
	 * add an event listener.
	 */
	MainScene(Vector2 resolution);
	/**
	 * removes the event listener.
	 */
	~MainScene();

	/**
	 * receives all evenets and calls the member functions.
	 */
	void OnEvent(Event const& event) override;
};