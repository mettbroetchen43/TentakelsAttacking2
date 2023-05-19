//
// Purpur Tentakel
// 01.11.2022
//

#pragma once
#include "Scene.h"

class SliderAndInputLine;

/**
 * provides a scenes, where the global settings can be set.
 */
class SettingsScene final : public Scene {
private:
	std::shared_ptr<SliderAndInputLine> m_volume; ///< contains the volume slider
	std::vector<std::pair<Resolution, std::string>> m_rawResolutionEntries; ///< contains die raw resolution information

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(SceneType continueScene);

	/**
	 * returns the strings out of the raw resolution data.
	 */
	std::vector<std::string> GetStringsFromResolutionEntries() const;
	/**
	 * returns index from resolution enum.
	 */
	int GetIndexFromResolution(Resolution resolution) const;

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	SettingsScene(Vector2 resolution, SceneType continueScene);
};
