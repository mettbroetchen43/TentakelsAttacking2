//
// Purpur Tentakel
// 24.10.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include "GenerelEvents.hpp"

class CheckBox;
enum class GameEventTypes;

/**
 * provides a scene where the game evenets can be set.
 */
class GameEventSettings : public Scene, public EventListener {
private:
	std::vector<std::shared_ptr<CheckBox>> m_checkBoxes; ///< contains all check boxes

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
	 * sets the checksboxes when logic calls it via event.
	 * calls set global checkbox.
	 */
	void UpdateElements(UpdateCheckGameEventsUI const* event);
	/**
	 * calulates if the global checkbox should be set.
	 * updates the checkbox.
	 */
	void SetGlobalCheckbox();

public:
	/**
	 * ctor.
	 * add an event listener.
	 * triggers logic to send the initial dasa via event.
 	 */
	GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution);
	/**
	 * dtor.
	 * removes an eventr listener.
	 */
	~GameEventSettings();

	/**
	 * receives all events and calles the member functions.
	 */
	void OnEvent(Event const& event);

	/**
	 * sets random values for every checkbox except for the gloabl checkpox.
	 * calls global checkbox to set.
	 */
	void SetRandom();
};
