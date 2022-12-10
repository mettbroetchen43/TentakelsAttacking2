//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "UIElement.hpp"
#include "EventListener.hpp"	
#include "AppContext.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Focus.h"
#include <vector>
#include <memory>

class Scene;

/**
 * mamages the complete UI.
 * contains the logic and calls it to update.
 */
class UIManager final : public EventListener {
private:
	AppContext& m_appContext; ///< contains a AppContext ref.
	Focus m_focus; ///< contains the focus system.
	SceneManager m_sceneManager; ///< contains the scene manager.
	GameManager m_gameManager; ///< contains the game logic
	Vector2 m_resolution; ///< contains the current resolution of the window
	bool m_closeWindow = false; ///< contains if the game will quit at the end of the tick
	Resolution m_nextResolution;

	/**
	 * Toggles between follscreen and window mode.
	 */
	void ToggleFullScreen(bool first = false);

	/**
	 * converts and Updates the reosultion in Window mode.
	 */
	void CheckAndSetNewResolution ( );

	/**
	 * calls the game logic to update.
	 * checks the quit input.
	 * checks the fullscreen toggle.
	 * calls the focus and uimanager to update.
	 */
	void CheckAndUpdate();
	/**
	 * start drawing.
	 * draws the background black.
	 * calls the uimanager to render.
	 * calls the focus to render.
	 * draws the FPS in debug build.
	 * ends drawing.
	 */
	void Render();

	/**
	 * sets the target FPS in the raylib.
	 */
	void SetTargetFPS(SetTargetFPSEvent const* event);
	/**
	 * main loop of the programm.
	 * loops while not should close.
	 * calls check resolution.
	 * calls generell update.
	 * calls render.
	 */
	void UILoop();

public:
	/**
	 * ctor.
	 * sets ecit key in raylib to none.
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

	/**
	 * receives all events and calls the member functions.
	 */
	void OnEvent(Event const& event);

	/**
	 * returns the current resolution of the current monitor.
	 */
	[[nodiscard]] Vector2 GetResolution() const;
	/**
	 * returns an reference if the current focus instance.
	 */
	[[nodiscard]] Focus& GetFocus();
};