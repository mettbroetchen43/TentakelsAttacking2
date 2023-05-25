//
// Purpur Tentakel
// 31.10.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include <vector>

class GameEventSettings;
class SliderAndInputLine;
enum class SliderType;

/**
 * provides a scene where you can set the game parameter of an new game.
 */
class NewGameParameterScene final : public Scene, public EventListener {
private:
	std::shared_ptr<GameEventSettings> m_eventSettings; ///< contains a scene that provides the game event settings
	std::vector<std::shared_ptr<SliderAndInputLine>> m_slider; ///< contains all slider to set values

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution); 

	/**
	 * sets the value of the slider by there id.
	 */
	void SetValue(int value, SliderType type) const;
	/**
	 * calls the event setting and slider to set random values.
	 */
	void SetRandom() const;

	/**
	 * calls the next scene via an event.
	 */
	void NextScene() const;

public:
	/**
	 * ctor.
	 * adds an event listener.
	 */
	NewGameParameterScene(Vector2 resolution);
	/**
	 * dtor.
	 * removes an event listener.
	 */
	~NewGameParameterScene() override;

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event) override;
};
