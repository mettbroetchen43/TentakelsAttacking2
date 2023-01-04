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
	std::vector<std::pair<Resolution, std::string>> m_rawResolutionEntries; ///< contains die raw resolution information

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();

	/**
	 * returs the strings out of the raw resolution data.
	 */
	std::vector<std::string> GetStringsFromResolutionEntries() const;

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	SettingsScene(Vector2 resolution);
};