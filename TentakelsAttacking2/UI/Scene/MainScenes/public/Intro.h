//
// Purpur Tentakel
// 12.09.2022
//

#pragma once
#include "Scene.h"
#include "AppContext.h"
#include "SceneType.h"
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <functional>

class ClassicButton;
class Title;

/**
 * provides the intro scene.
 */
class Intro final : public Scene {
private:
	std::shared_ptr<Title> m_title = nullptr; ///< contains the title
	std::shared_ptr<ClassicButton> m_btn = nullptr; ///< contains the next button.
	bool m_btnMovmendFinish = false; ///< contains if the button has finished moving
	SceneType m_nextScene = SceneType::MAIN_MENU; ///< contains the next Scene Type that will be loaded
	
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
	Intro(Vector2 resolution);

	/**
	 * calls tite to animate, then enables and moves the button.
	 * checks for skip input.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	/**
	 * calls all elements to render.
	 */
	void Render(AppContext const& appContext);
	/**
	 * calls all elements to resize.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;
	/**
	 * sets scene active.
	 * selects the button as focus.
	 */
	void SetActive(bool active, AppContext const& appContext) override;
};