//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "UIElement.h"
#include "EventListener.hpp"	
#include "AppContext.h"
#include "SceneManager.h"
#include "Focus.h"
#include <vector>
#include <memory>

class Scene;

class UIManager : public EventListener {
private:
	AppContext& m_appContext;
	Focus m_focus;
	SceneManager m_sceneManager;
	Vector2 m_resolution;
	bool m_closeWindow;

	void ToggleFullScreen();

	void CheckAndUpdateResolution();
	void CheckAndUpdate();
	void Render();

	void UILoop();

public:
	UIManager();

	void StartUI();

	void OnEvent(Event const& event);

	[[nodiscard]] Vector2 GetResolution() const;
	[[nodiscard]] Focus& GetFocus();
};