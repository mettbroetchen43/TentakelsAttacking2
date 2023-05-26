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
	ColorPicker* m_colorPicker; ///< contains the color picker where the player color gets choose
	Table* m_table; ///< contains the table where the current player where displayed
	ClassicButton_ty m_nextBTN; ///< contains the button, witch the calls the next scene
	std::vector<Focusable_ty_raw> m_nestedFocus; ///< contains Focusable_ty_raw that are abe to have an nested focus
	std::vector<ClassicButton_ty> m_playerButtons; ///< contains the remove player buttons

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution, AppContext_ty appContext);
	/**
	 * initializes remove player button.
	 * connects the actions.
	 */
	void InitializePlayerButtons(AppContext_ty appContext);
	/**
	 * checks  if the element has an nested focus and if the mouse position is outside the curtain collider.
	 * if so, a focus layer gets deleted and the nested focus gets set to false.
	 */
	void CheckForNestedFocus(Vector2 const& mousePosition,
		AppContext_ty_c appContext) const;

	/**
	 * updates the scene elements when a player gets added / edit / deleted.
	 */
	void UpdateSceneEntries(AppContext_ty_c appContext);

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
		Color color, AppContext_ty_c appContext);
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
	 * deletes an player via event.
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
	void SetNextButton(AppContext_ty_c appContext);

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
		AppContext_ty_c appContext) override;
	/**
	 * renders the scene.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resize the scene.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event) override;
};
