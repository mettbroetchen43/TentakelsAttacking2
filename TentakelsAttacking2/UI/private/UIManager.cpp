//
// Purpur Tentakel
// 24.08.2022
//

#include "UIManager.h"
#include "TestScene.h"

Vector2 UIManager::GetResolution() const {
	Vector2 newResolution;
	int display = GetCurrentMonitor();
	newResolution.x = static_cast<float>(GetMonitorWidth(display));
	newResolution.y = static_cast<float>(GetMonitorHeight(display));
	return newResolution;
}
Focus& UIManager::GetFocus() {
	return m_focus;
}
void UIManager::ToggleFullScreen() {
	ToggleFullscreen();
	if (!IsWindowFullscreen()) {
		SetWindowPosition(0, 0);
	}
}
void UIManager::CheckAndUpdateResolution() {
	Vector2 newResolution = GetResolution();

	bool isNewResolution = (m_resolution.x != newResolution.x)
		or (m_resolution.y != newResolution.y);

	if (isNewResolution) {
		m_resolution = newResolution;
		SetWindowSize(static_cast<int>(m_resolution.x), static_cast<int>(m_resolution.y));
		m_sceneManager.Resize(newResolution, m_appContext);
	}
}

void UIManager::CheckAndUpdate() {
	m_gameManager.Update();

	bool quit = 
		IsKeyDown(KeyboardKey::KEY_LEFT_ALT)
		and IsKeyPressed(KeyboardKey::KEY_F4);
	if (quit) {
		auto event = CloseWindowEvent();
		m_appContext.eventManager.InvokeEvent(event);
	}

	if (IsKeyPressed(KEY_F11)) {
		ToggleFullScreen();
	}

	Vector2 mousePosition = GetMousePosition();
	m_focus.CheckAndUpdate();
	m_sceneManager.CheckAndUpdate(mousePosition, m_appContext);
}
void UIManager::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	m_sceneManager.Render(m_appContext);
	m_focus.Render();
	EndDrawing();
}

void UIManager::UILoop() {
	while (!WindowShouldClose()) {
		CheckAndUpdateResolution();
		CheckAndUpdate();
		Render();
		if (m_closeWindow) {
			break;
		}
	}
	StopSoundMulti();
	CloseWindow();

}

UIManager::UIManager()
	: m_appContext(AppContext::GetInstance()), m_resolution({ 0.0f,0.0f }), m_sceneManager(this) {
	SetTargetFPS(60);
	SetExitKey(KeyboardKey::KEY_NULL);

	m_resolution = GetResolution();
	SetWindowSize(static_cast<int>(m_resolution.x), static_cast<int>(m_resolution.y));
	m_appContext.eventManager.AddListener(this);
}

void UIManager::StartUI() {
	auto event = SwitchSceneEvent(SceneType::LOGO);
	m_appContext.eventManager.InvokeEvent(event);
	if (m_appContext.IsMaximizedStartingWindow()) {
		ToggleFullScreen();
	}
	else {
		SetWindowPosition(0,0);
	}

	UILoop();
}

void UIManager::OnEvent(Event const& event) {
	if (auto const& CloseEvent = dynamic_cast<CloseWindowEvent const*>(&event)) {
		m_closeWindow = true;
	}
}
