//
// Purpur Tentakel
// 24.08.2022
//

#include "UIManager.h"
#include "TestScene.h"

Vector2 UIManager::GetResolution() const {
	Vector2 newResolution;
	int display = GetCurrentMonitor();
	newResolution.x = GetMonitorWidth(display);
	newResolution.y = GetMonitorHeight(display);
	return newResolution;
}
Focus& UIManager::GetFocus() {
	return m_focus;
}
void UIManager::CheckAndUpdateResolution() {
	Vector2 newResolution = GetResolution();
	if (m_resolution.x != newResolution.x ||
		m_resolution.y != newResolution.y) {
		m_resolution = newResolution;
		SetWindowSize(m_resolution.x, m_resolution.y);
		m_sceneManager.Resize(newResolution);
	}
}

void UIManager::CheckAndUpdate() {
	Vector2 mousePosition = GetMousePosition();
	m_focus.CheckAndUpdate();
	m_sceneManager.CheckAndUpdate(mousePosition, m_appContext);
}
void UIManager::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	m_focus.Render();
	m_sceneManager.Render();
	EndDrawing();
}

void UIManager::UILoop() {
	while (!WindowShouldClose()) {
		CheckAndUpdateResolution();
		CheckAndUpdate();
		Render();
	}
	CloseWindow();

}

UIManager::UIManager()
	: m_appContext(AppContext::GetInstance()), m_resolution({ 0.0f,0.0f }), m_sceneManager(this) {
	SetTargetFPS(60);

	m_resolution = GetResolution();
	SetWindowSize(m_resolution.x, m_resolution.y);
}

void UIManager::StartUI() {
	m_sceneManager.SwitchScene(SceneType::TEST);
	UILoop();
}

