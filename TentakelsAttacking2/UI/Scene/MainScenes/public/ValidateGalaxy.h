//
// Purpur Tentakel
// 20.11.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include <memory>

class GalaxyAndSlider;
class SendGalaxyPointerEvent;

class ValidateGalaxyScene : public Scene, public EventListener {
private:
	std::shared_ptr<GalaxyAndSlider> m_galaxy;

	void Initialize();

	void InitializeGalaxy(SendGalaxyPointerEvent const*);

	void NewGalaxy();

public:
	ValidateGalaxyScene(Vector2 resolution);
	~ValidateGalaxyScene();

	void OnEvent(Event const& event) override;
};

