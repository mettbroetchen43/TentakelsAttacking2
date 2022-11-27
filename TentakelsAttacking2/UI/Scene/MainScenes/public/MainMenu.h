//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "Scene.h"

/**
 * provides the main menu scene.
 */
class MainMenu final : public Scene {
private:
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution, AppContext& appContext);
public:
	/**
	 * ctor.
	 * initialization.
	 */
	MainMenu(Vector2 resolution);
};
