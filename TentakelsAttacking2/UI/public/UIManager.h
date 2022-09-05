//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "UIElement.h"
#include "AppContext.h"
#include "SceneManager.h"
#include "Focus.h"
#include <vector>
#include <memory>

class Scene;

class UIManager {
private:
	AppContext& m_appContext;
	Focus m_focus;
	SceneManager m_sceneManager;
	Vector2 m_resolution;

	void CheckAndUpdateResolution();
	void CheckAndUpdate();
	void Render();

	void UILoop();

public:
	UIManager();

	void StartUI();

	[[nodiscard]] Vector2 GetResolution() const;
	[[nodiscard]] Focus& GetFocus();
};