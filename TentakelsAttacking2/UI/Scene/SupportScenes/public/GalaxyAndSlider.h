//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "Scene.h"
#include "CLogicAlias.hpp"
#include <vector>

class Slider;
class Line;
class ClassicButton;
class UIGalaxy;

/**
 * provides a scene that can display the logic galaxy.
 */
class GalaxyScene final : public Scene {
private:
	bool m_isEnabled = true; ///< contains id it is enabled
	Line_ty m_scaleLineX; ///< contains the line that displays the scale in X direction
	Line_ty m_scaleLineY; ///< contains the line that displays the scale in Y direction
	Slider_ty m_verticalSlider; ///< contains the slider that slides in Y direction
	Slider_ty m_horizontalSlider; //< contains the slider that slides in X direction
	ClassicButton_ty m_zoomInBtn; ///< contains the button to zoom in
	ClassicButton_ty m_zoomOutBtn; ///< contains the button to zoom out
	std::shared_ptr<UIGalaxy> m_galaxy; ///< contains the ui galaxy

	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution, bool isShowGalaxy);
	/**
	 * updates the slider and scale lines.
	 */
	void Zoom(float scaleFactor, Vector2 referenceScale);
	/**
	 * updates the slider.
	 */
	void Slide(float position, bool isHorisontal);

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution, bool isShowGalaxy = false);

	/**
	 * loop that setting through to the galaxy.
	 */
	void SetIsScaling(bool isScaling);
	/**
	 * returns if the galaxy is able to scale.
	 */
	[[nodiscard]] bool IsScaling() const;

	/**
	 * sets if the scene is enabled.
	 * sets galaxy, and zoom button separated enabled.
	 */
	void SetIsEnabled(bool isEnabled);
	/**
	 * returns if the scene is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const;

	/**
	 * return the current ui galaxy.
	 */
	[[nodiscard]] Galaxy_ty_raw GetGalaxy() const;

	/**
	 * updates the scene.
	 * updates the scale buttons only if scaling.
	 * updates the slider only if the galaxy is actually scaled.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the scene.
	 * renders the scale buttons and scale lines only if scaling.
	 * renders the slider only if the galaxy is actually scaled.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resize the scene.
	 * resize the scale buttons, scale lines and buttons seperated.
	 * 
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
