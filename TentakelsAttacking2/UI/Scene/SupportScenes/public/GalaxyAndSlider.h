//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "Scene.h"
#include "EventListener.hpp"
#include <vector>

class Galaxy;
class Slider;
class ClassicButton;

class GalaxyScene final : public Scene, public EventListener {
private:
	Vector2 m_resolution;
	Galaxy const* m_currentGalaxy;
	Rectangle m_galaxyColider;
	std::vector<UIElement> m_galaxyElements;
	std::shared_ptr<Slider> m_verticalSlider;
	std::shared_ptr<Slider> m_horisontalSlider;
	std::shared_ptr<ClassicButton> m_zoomInBtn;
	std::shared_ptr<ClassicButton> m_zoomOutBtn;

	void Initialize();

	void UpdateGalaxy();

public:
	GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution);

	void OnEvent(Event const& event) override;

	void Render(AppContext const& appContext) override;
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
};
