//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "Scene.h"
#include "SceneType.h"
#include <memory>

class GalaxyScene;

class MainScene : public Scene {
private:
	enum class MainSceneType {
		GALAXY,
		PLANET_TABLE,
		FLEET_TABLE,
	};

	std::shared_ptr<GalaxyScene> m_galaxy;
	// std::shared_ptr<GalaxyScene> m_planetTable;
	// std::shared_ptr<GalaxyScene> m_fleetTable;

	void Initialize();

	void Switch(MainSceneType sceneType);

public:
	MainScene(Vector2 resolution);
};