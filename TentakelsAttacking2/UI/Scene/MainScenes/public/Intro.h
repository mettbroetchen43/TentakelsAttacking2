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

/**
 * provides the intro scene.
 */
class Intro final : public Scene {
private:
	Title_ty m_title{ nullptr }; ///< contains the title
	ClassicButton_ty m_btn{ nullptr }; ///< contains the next button.
	bool m_btnMovementFinish{ false }; ///< contains if the button has finished moving
	SceneType m_nextScene{ SceneType::MAIN_MENU }; ///< contains the next Scene Type that will be loaded
	
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
	 * calls title to animate, then enables and moves the button.
	 * checks for skip input.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext);
	/**
	 * calls all elements to render.
	 */
	void Render(AppContext_ty_c appContext);
	/**
	 * calls all elements to resize.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
	/**
	 * sets scene active.
	 * selects the button as focus.
	 */
	void SetActive(bool active, AppContext_ty_c appContext) override;
};
