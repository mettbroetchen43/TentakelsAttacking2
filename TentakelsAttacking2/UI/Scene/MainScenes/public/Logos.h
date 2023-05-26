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

/**
 * provides the logo scene
 */
class LogoScene final : public Scene {
private:
	inline static float  const m_sceneLength{ 5.0f }; ///< defines the scene length in seconds
	SceneType m_nextScene{ SceneType::INTRO }; ///< contains the type of the next scene that gets called after this one
	double m_time; ///< contains the program time at the initialization of this scene

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
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * returns if not active.
	 * calls all elements to render.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * returns if not active.
	 * calls all elements to resize.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
