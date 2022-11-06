//
// Purpur Tentakel
// 01.11.2022
//

#pragma once
#include "Scene.h"

class SliderAndInputLine;

class SettingsScene final : public Scene {
private:
	std::shared_ptr<SliderAndInputLine> m_volume;

	void Initialize(Vector2 resolution);

public:
	SettingsScene(Vector2 resolution);
};