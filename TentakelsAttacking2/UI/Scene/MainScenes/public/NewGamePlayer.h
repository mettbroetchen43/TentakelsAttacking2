//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "Scene.h"
#include "InputLine.hpp"
#include "AbstractTableCell.h"
#include "EventListener.hpp"

class ColorPicker;
class Table;
class Focusable;
class ClassicButton;

/**
 * provides a scene where the player can be edit of a new game.
 */
class NewGamePlayerScene final : public Scene, public EventListener {
private:
	InputLine<std::string>* m_inputLine; ///< contains an input line where the player name where entered
	ColorPicker* m_colorPicker; ///< contains the color picker where the player color gets choosen
	Table* m_table; ///< contains the table where the current playere where displayed
	std::shared_ptr<ClassicButton> m_nextBTN; ///< contains the button, witch the calls the next scene
	std::vector<Focusable*> m_nestedFocus; ///< contains focusable* that are abe to have an nested focus
	std::vector<std::shared_ptr<ClassicButton>> m_playerButtons; ///< contains the remove player buttons

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution, AppContext& appContext);
	/**
	 * initializes remove player button.
	 * connects the actions.
	 */
	void InitializePlayerButtons(AppContext& appContext);
	/**
	 * checks  if the element has an nested focus and if the mouse position is outside the curtain collider.
	 * if so, a focus layer gets deleted and the nested focus gets set to false.
	 */
	void CheckForNestedFocus(Vector2 const& mousePosition,
		AppContext const& appContext) const;

	/**
	 * updates the scene elements when a player gets added / edit / deleted.
	 */
	void UpdateSceneEntries(AppContext const& appContext);

	/**
	 * adds a new player via event.
	 * calls the scene elements to update.
	 */
	void AddPlayer();
	/**
	 * updates a player via event.
	 * calls the scene elements to update.
	 */
	void UpdatePlayer(unsigned int ID, std::string const& name,
		Color color, AppContext const& appContext);
	/**
	 * updates a player name.
	 * calls the update player.
	 */
	void UpdatePlayerName(AbstractTableCell const* cell,
		std::string oldValue, std::string newValue);
	/**
	 * updates a player color.
	 * calls the update player.
	 */
	void UpdatePlayerColor(AbstractTableCell const* cell,
		Color oldValue, Color newValue);
	/**
	 * updates a player color.
	 * calls the update player.
	 */
	void CreateDeletePlayer();
	/**
	 * ceates an popup to get the id that should get deleted.
	 */
	void DeletePlayer(unsigned int ID);
	/**
	 * checks the player count in the logic via event.
	 */
	void CheckPlayerCount() const;
	/**
	 * returns if its not valid next scene.
	 * loads the next scene via event.
	 */
	void NextScene(bool valid);
	/**
	 * deletes all player data via event.
	 * updates all scene elements.
	 */
	void Reset();

	/**
	 * sets the next scene button enables or disabled whether the player count is valid.
	 */
	void SetNextButton(AppContext const& appContext);

public:
	/**
	 * ctor.
	 * add an event listener.
	 */
	NewGamePlayerScene(Vector2 resolution);
	/**
	 * dtor.
	 * removes an event listener.
	 */
	~NewGamePlayerScene();

	/**
	 * updates the scene.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	/**
	 * renders the scene.
	 */
	void Render(AppContext const& appContext) override;
	/**
	 * resize the scene.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	/**
	 * receives all events and calles the member functions.
	 */
	void OnEvent(Event const& event) override;
};
