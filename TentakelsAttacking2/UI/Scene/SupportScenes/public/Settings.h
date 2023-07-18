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
class SettingsScene : public Scene{
private:
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	SettingsScene(Vector2 resolution);

	/**
	 * updates all elements in elements.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders all elements in elements and elements out update.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes all elements in elements and elements out update.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
