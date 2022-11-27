//
// Purpur Tentakel
// 01.11.2022
//

#pragma once
#include "Scene.h"

class SliderAndInputLine;

/**
 * privides a scenes, where the global settings can be set.
 */
class SettingsScene final : public Scene {
private:
	std::shared_ptr<SliderAndInputLine> m_volume; ///< contains the volume slider

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution);

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	SettingsScene(Vector2 resolution);
};