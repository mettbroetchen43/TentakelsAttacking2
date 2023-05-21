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
class PlanetTable;
class FleetTable;
class ClassicButton;
class Text;
template<typename T>
class InputLine;

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
	MainSceneType m_currentMainSceneType{ MainSceneType::GALAXY }; ///< contains witch scenetype is currently loaded

	std::shared_ptr<GalaxyScene> m_galaxy; ///< contains the current ui galaxy
	std::shared_ptr<PlanetTable> m_planetTable; ///< contains the current planet table
	std::shared_ptr<FleetTable> m_fleetTable; ///< contains the current fleet table
	std::shared_ptr<ClassicButton> m_nextBtn; ///< contains the next turn / round button
	std::shared_ptr<Text> m_currentPlayerName; ///< contains the current player name
	std::shared_ptr<Text> m_nextPlayerName; ///< contains the next player name
	std::shared_ptr<Text> m_currentRound;  ///< contains the current round count
	std::shared_ptr<Text> m_currentTargetRound;  ///< contains the current target round count
	PlayerData m_currentPlayer; ///< contains the data of the current player
	PlayerData m_nextPlayer; ///< contains the data of the next player

	std::shared_ptr<InputLine<int>> m_origin; ///< provides the origin planet ID
	std::shared_ptr<InputLine<int>> m_destination; ///< provides the destination planet ID
	std::shared_ptr<InputLine<int>> m_destinationX; ///< provides the destination planet X
	std::shared_ptr<InputLine<int>> m_destinationY; ///< provides the destination planet Y
	std::shared_ptr<InputLine<int>> m_shipCount; ///< provides the ship count

	std::shared_ptr<ClassicButton> m_acceptBtn; ///< sends the fleet event into the logic
	std::shared_ptr<ClassicButton> m_resetBtn; ///< clears the input lines

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();
	/**
	 * removes old ui galaxy if one exists.
	 * initializes a new ui galaxy.
	 */
	void InitializeGalaxy();
	/**
	 * removes old planet table if one exists.
	 * initializes a new planet table.
	 */
	void InitializePlanetTable();

	/**
	 * removes old fleet table if one exists.
	 * initializes a new fleet table.
	 */
	void InitializeFleetTable();

	/**
	 * stitches the support scene to clear.
	 * updates player text and initializes a new galaxy.
	 * generates an popup.
	 */
	void NextTurn();
	/**
	 * updates player text and rounds.
	 * initializes a new galaxy.
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

	/**
	 * return if any input line in in focus.
	 */
	bool HasAnyInputLineFocus();

	/**
	 * sets the accept button active or inactive.
	 */
	void SetAcceptButton();

	/**
	 * sends the ship instruction event.
	 */
	void SendFleetInstruction();
	/**
	 * resets the input lines
	 */
	void ClearInputLines();

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
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event) override;

	/**
	 * updates all elements in elements.
	 * calls the CheckAndUpdate from the Scene.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
};
