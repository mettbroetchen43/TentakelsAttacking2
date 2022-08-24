//
// Purpur Tentakel
// 24.08.2022
//

#include "UIManager.h"

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
		for (auto element : m_elements) {
			element->Resize(m_resolution);
		}
	}
}

void UIManager::CheckAndUpdate() {
	Vector2 mousePosition = GetMousePosition();
	for (auto element : m_elements) {
		element->CheckAndUpdate(mousePosition);
	}
}

void UIManager::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	for (auto element : m_elements) {
		element->Render();
	}
	EndDrawing();
}

UIManager::UIManager()
	: m_resolution(Vector2(0.0f,0.0f)), m_soundManager(SoundManager()) {
	SetTargetFPS(60);

	InitWindow(100.0f, 100.0f, "raylib [core] example - basic window");
	m_resolution = GetResolution();
	SetWindowSize(m_resolution.x, m_resolution.y);
}

void UIManager::UILoop() {
	while (!WindowShouldClose()) {
		CheckAndUpdateResolution();
		CheckAndUpdate();
		Render();
	}
	CloseWindow();

}

void UIManager::AddElement(std::shared_ptr<UIElement> newElement) {
	m_elements.push_back(newElement);
}
