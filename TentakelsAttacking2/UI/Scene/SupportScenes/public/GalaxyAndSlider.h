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
	float m_scaleFacor = 1.0f;
	Vector2 m_resolution;
	Galaxy const* m_currentGalaxy;
	Rectangle m_galaxyColiderDraw;
	Rectangle m_galaxyColider;
	Rectangle m_colider;
	std::vector<std::shared_ptr<UIElement>> m_galaxyElements;
	std::shared_ptr<Slider> m_verticalSlider;
	std::shared_ptr<Slider> m_horisontalSlider;
	std::shared_ptr<ClassicButton> m_zoomInBtn;
	std::shared_ptr<ClassicButton> m_zoomOutBtn;

	void Initialize();

	void UpdateGalaxy();

	void SetScale(bool ScaleIn);

public:
	GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution);
	~GalaxyScene();

	void OnEvent(Event const& event) override;

	void Render(AppContext const& appContext) override;
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
};
