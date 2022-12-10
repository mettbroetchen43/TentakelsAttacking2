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
		auto& fullScreen = AppContext::GetInstance().constants.window.startingModeFullScreen;
		fullScreen = !fullScreen;
	}
}

void UIManager::CheckAndSetNewResolution () {
	if ( m_nextResolution == m_appContext.constants.window.current_resolution ) { return; }

	m_appContext.constants.window.current_resolution = m_nextResolution;
	auto values = m_appContext.constants.window.GetIntFromResolution ( m_nextResolution );
	m_resolution = { static_cast<float>(values[1]), static_cast<float>(values[0]) };

	SetWindowSize ( values[0], values[1] );
	m_sceneManager.Resize ( m_resolution, m_appContext );
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
		CheckAndSetNewResolution ( );
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
	: m_appContext(AppContext::GetInstance()), m_resolution(GetResolution()), m_sceneManager(this) {
	
	SetExitKey(KeyboardKey::KEY_NULL);

	SetWindowSize(static_cast<int>(m_resolution.x), static_cast<int>(m_resolution.y));
	m_appContext.eventManager.AddListener(this);

	Print("UIManager", PrintType::INITIALIZE);
}

UIManager::~UIManager() {
	m_appContext.eventManager.RemoveListener(this);
}

void UIManager::StartUI() {
	m_nextResolution = m_appContext.constants.window.current_resolution;

	auto event = SwitchSceneEvent(SceneType::LOGO);
	m_appContext.eventManager.InvokeEvent(event);
	if (m_appContext.constants.window.startingModeFullScreen) {
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

	if ( auto const *ResolutionEvent = dynamic_cast<SetNewResolutionEvent const *>(&event) ) {
		m_nextResolution = ResolutionEvent->GetResolution ( );
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
