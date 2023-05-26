//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include "GenerelEvents.hpp"

enum class GameEventTypes;

/**
 * provides a scene where the game events can be set.
 */
class GameEventSettings : public Scene, public EventListener {
private:
	std::vector<CheckBox_ty> m_checkBoxes; ///< contains all check boxes

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resoluton, unsigned int focusID);

	/**
	 * sets the checkbox checkt with the provided id via event.
	 */
	void SetChecked(unsigned int ID, bool isCecked);

	/**
	 * sets the checkboxes when logic calls it via event.
	 * calls set global checkbox.
	 */
	void UpdateElements(UpdateCheckGameEventsUI const* event);
	/**
	 * calculates if the global checkbox should be set.
	 * updates the checkbox.
	 */
	void SetGlobalCheckbox();

public:
	/**
	 * ctor.
	 * add an event listener.
	 * triggers logic to send the initial data via event.
 	 */
	GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);
	/**
	 * dtor.
	 * removes an event listener.
	 */
	~GameEventSettings();

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event);

	/**
	 * sets random values for every checkbox except for the global checkbox.
	 * calls global checkbox to set.
	 */
	void SetRandom();
};
