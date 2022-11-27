//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "Scene.h"
#include "SceneType.h"
#include <functional>

struct AppContext;
enum class SceneType;
#define SCENE_LENGTH 5.0 ///< defines the scene lengst in seconds

/**
 * provides the logo scene
 */
class LogoScene final : public Scene {
private:
	SceneType m_nextScene = SceneType::INTRO; ///< contains the type of the next scene that gets called after this one
	double m_time; ///< vontains the programm time at the initialuízation of this scene

	/**
	 * initializes all ui elements.
	 */
	void Initialize();

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	LogoScene(Vector2 resolution);

	/**
	 * returns if not active.
	 * calls all elements to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * returns if not active.
	 * calls all elements to render.
	 */
	void Render(AppContext const& appContext) override;
	/**
	 * returns if not active.
	 * calls all elements to resize.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
