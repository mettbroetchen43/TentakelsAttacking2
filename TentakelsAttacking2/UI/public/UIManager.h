//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "UIElement.hpp"
#include "EventListener.hpp"	
#include "AppContext.h"
#include "SceneManager.h"
#include "HoverRender.h"
#include "GameManager.h"
#include "Focus.h"
#include <vector>
#include <memory>

class Scene;

/**
 * manages the complete UI.
 * contains the logic and calls it to update.
 */
class UIManager final : public EventListener {
private:
	AppContext_ty m_appContext; ///< contains a AppContext ref.
	Focus m_focus; ///< contains the focus system.
	SceneManager m_sceneManager; ///< contains the scene manager.
	GameManager m_gameManager; ///< contains the game logic
	HoverRender m_hover;
	Vector2 m_resolution; ///< contains the current resolution of the window
	bool m_closeWindow{ false }; ///< contains if the game will quit at the end of the tick
	Resolution m_nextResolution; ///< contains the resolution of the next frame

	/**
	 * Toggles between full screen and window mode.
	 */
	void ToggleFullScreen(bool first = false);

	/**
	 * converts and updates the resolution in Window mode.
	 */
	void CheckAndSetNewResolution();

	/**
	 * checks the quit input.
	 * checks the full screen toggle.
	 * calls the focus and UImanager to update.
	 */
	void CheckAndUpdate();
	/**
	 * start drawing.
	 * draws the background black.
	 * calls the UImanager to render.
	 * calls the focus to render.
	 * draws the FPS in debug build.
	 * ends drawing.
	 */
	void Render();

	/**
	 * sets the current window size from the config to raylib.
	 */
	void SetWindowSize(bool fullscreen);
	/**
	 * sets the pint ow position if in window mode.
	 */
	void SetWindowPosition();
	/**
	 * sets the target FPS in the raylib.
	 */
	void SetTargetFPS(SetTargetFPSEvent const* event);
	/**
	 * main loop of the program.
	 * loops while not should close.
	 * calls check resolution.
	 * calls generell update.
	 * calls render.
	 */
	void UILoop();

public:
	/**
	 * ctor.
	 * sets edit key in raylib to none.
	 * resize window.
	 * add event listener.
	 */
	UIManager();
	/**
	 * dtor.
	 * removes listener.
	 */
	~UIManager();

	/**
	 * main loop entry.
	 * sets initial scene.
	 * sets initial window mode.
	 * calls the ui loop (main loop).
	 */
	void StartUI();


	void StartUILoop();

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event);
	/**
	 * return the current resolution.
	 */
	[[nodiscard]] Vector2 GetResolution() const;
	/**
	 * returns an reference if the current focus instance.
	 */
	[[nodiscard]] Focus& GetFocus();
};
