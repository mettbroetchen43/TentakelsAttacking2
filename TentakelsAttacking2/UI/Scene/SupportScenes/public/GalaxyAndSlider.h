//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "Scene.h"
#include <vector>

class Slider;
class ClassicButton;
class UIGalaxy;

class GalaxyScene final : public Scene {
private:
	std::shared_ptr<Slider> m_verticalSlider;
	std::shared_ptr<Slider> m_horisontalSlider;
	std::shared_ptr<ClassicButton> m_zoomInBtn;
	std::shared_ptr<ClassicButton> m_zoomOutBtn;
	std::shared_ptr<UIGalaxy> m_galaxy;

	void Initialize(Vector2 resolution);
	void Zoom(float scaleFactor);
	void Slide(float position, bool isHorisontal);

public:
	GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution);

	void SetIsScaling(bool isScaling);
	[[nodiscard]] bool IsScaling() const;

	void Render(AppContext const& appContext) override;
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
