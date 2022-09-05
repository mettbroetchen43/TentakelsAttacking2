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
void UIManager::CheckAndUpdateResolution() {
	Vector2 newResolution = GetResolution();
	if (m_resolution.x != newResolution.x ||
		m_resolution.y != newResolution.y) {
		m_resolution = newResolution;
		SetWindowSize(m_resolution.x, m_resolution.y);
		for (auto scene : m_scenes) {
			scene->Resize(m_resolution);
		}
	}
}

void UIManager::CheckAndUpdate() {
	Vector2 mousePosition = GetMousePosition();
	m_focus.CheckAndUpdate();
	for (auto scene : m_scenes) {
		scene->CheckAndUpdate(mousePosition, m_appContext);
	}
}
void UIManager::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	m_focus.Render();
	for (auto scene : m_scenes) {
		scene->Render();
	}
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
	: m_appContext(AppContext::GetInstance()), m_resolution(Vector2(0.0f,0.0f)) {
	SetTargetFPS(60);

	m_resolution = GetResolution();
	SetWindowSize(m_resolution.x, m_resolution.y);
}

void UIManager::StartUI() {
	auto scene = std::make_shared<TestScene>(Vector2(1.0f,1.0f), Vector2(0.0f,0.0f), true, *this);
	m_scenes.emplace_back(scene);
	UILoop();
}

