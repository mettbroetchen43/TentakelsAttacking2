//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"

class ClassicButton;

/**
 * provides the main menu scene.
 */
class MainMenu final : public Scene, public EventListener {
private:
	std::shared_ptr<ClassicButton> m_continueBtn;
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution, AppContext& appContext);

public:
	/**
	 * initialization.
	 * adds scene as event listener
	 */
	MainMenu(Vector2 resolution);
	/**
	 * removes the scene as event listener.
	 */
	~MainMenu();
	/**
	 * collects the events.
	 */
	void OnEvent(Event const& event) override;
};
