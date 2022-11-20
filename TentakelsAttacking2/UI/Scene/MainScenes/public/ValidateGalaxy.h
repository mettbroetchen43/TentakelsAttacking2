//
// Purpur Tentakel
// 20.11.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include <memory>

class GalaxyScene;
class SendGalaxyPointerEvent;

class ValidateGalaxyScene : public Scene{
private:
	std::shared_ptr<GalaxyScene> m_galaxy;

	void Initialize();

	void InitializeGalaxy();

	void NewGalaxy();

public:
	ValidateGalaxyScene(Vector2 resolution);
};

