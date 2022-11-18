//
// Purpur Tentakel
// 24.08.2022
//

#include "UIManager.h"
#include "TestScene.h"
#include "HInput.h"
#include "HPrint.h"

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
void UIManager::ToggleFullScreen(bool first) {
	ToggleFullscreen();
	if (!IsWindowFullscreen()) {
		SetWindowPosition(0, 10);
	}
	if (!first) {
		auto& fullScreen = AppContext::GetInstance().constants.global.startingModeFullScreen;
		fullScreen = !fullScreen;
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

	if (IsQuitInput()) {
		auto event = CloseWindowEvent();
		m_appContext.eventManager.InvokeEvent(event);
	}

	if (IsToggleFullscreenInput()) {
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

#ifdef _DEBUG
	int fps = GetFPS();
	DrawTextEx(
		*(m_appContext.assetManager.GetFont()),
		("FPS: " + std::to_string(fps)).c_str(),
		Vector2(
			m_resolution.x * 0.94f,
			m_resolution.y * 0.01f),
		m_resolution.y * 0.03f,
		0.0f,
		WHITE
	);
#endif // _DEBUG

	EndDrawing();
}

void UIManager::SetTargetFPS(SetTargetFPSEvent const* event) {
	::SetTargetFPS(static_cast<int>(event->GetFPS()));
	Print("FPS Set: " + std::to_string(event->GetFPS()));
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
	
	SetExitKey(KeyboardKey::KEY_NULL);

	m_resolution = GetResolution();
	SetWindowSize(static_cast<int>(m_resolution.x), static_cast<int>(m_resolution.y));
	m_appContext.eventManager.AddListener(this);

	Print("UIManager", PrintType::INITIALIZE);
}

void UIManager::StartUI() {
	auto event = SwitchSceneEvent(SceneType::LOGO);
	m_appContext.eventManager.InvokeEvent(event);
	if (m_appContext.constants.global.startingModeFullScreen) {
		ToggleFullScreen(true);
	}
	else {
		SetWindowPosition(0,10);
	}

	Print("\"UI\" started");

	UILoop();
}

void UIManager::OnEvent(Event const& event) {
	if (auto const* CloseEvent = dynamic_cast<CloseWindowEvent const*>(&event)) {
		m_closeWindow = true;
		return;
	}

	if (auto const* ToggleEvent = dynamic_cast<ToggleFullscreenEvent const*>(&event)) {
		ToggleFullScreen();
		return;
	}

	if (auto const* FPSEvent = dynamic_cast<SetTargetFPSEvent const*>(&event)) {
		SetTargetFPS(FPSEvent);
		return;
	}
}
