//
// Purpur Tentakel
// 24.08.2022
//

#include "UIManager.h"
#include "TestScene.h"
#include "HInput.h"
#include "HPrint.h"

Focus& UIManager::GetFocus() {
	return m_focus;
}
void UIManager::ToggleFullScreen(bool first) {
	if (IsWindowFullscreen()) {
		::ToggleFullscreen();
		SetWindowSize(false);
		SetWindowPosition();
	}
	else {
		SetWindowSize(true);
		::ToggleFullscreen();
	}
	if(!first) {
		auto& fullScreen{ AppContext::GetInstance().constants.window.startingModeFullScreen };
		fullScreen = !fullScreen;
		m_sceneManager.Resize(m_resolution, m_appContext);
	}
}

void UIManager::CheckAndSetNewResolution() {
	if(m_nextResolution == m_appContext.constants.window.current_resolution) { return; }

	bool const validResolution{ m_appContext.constants.window.IsPossibleResolution(m_nextResolution) };
	if (!validResolution) { 
		Print(
			PrintType::ERROR,
			"invalid resolution for this screen -> {}",
			m_appContext.constants.window.GetStringFromResolution(m_nextResolution)
		);
		return;
	}

	m_appContext.constants.window.current_resolution = m_nextResolution;

	if (IsWindowFullscreen()) { return; }

	SetWindowSize(false);
	SetWindowPosition();

	m_sceneManager.Resize(m_resolution, m_appContext);
}

void UIManager::CheckAndUpdate() {
	if(IsQuitInput()) {
		CloseWindowEvent event;
		m_appContext.eventManager.InvokeEvent(event);
	}

	if(IsToggleFullscreenInput()) {
		ToggleFullScreen();
	}

	Vector2 const mousePosition{ GetMousePosition() };
	m_focus.CheckAndUpdate();
	m_sceneManager.CheckAndUpdate(mousePosition, m_appContext);
}
void UIManager::Render() {
	BeginDrawing();
	ClearBackground(BLACK);
	m_sceneManager.Render(m_appContext);
	m_focus.Render();
	m_hover.Render();

#ifdef _DEBUG
	int const fps{ GetFPS() };
	DrawTextEx(
		*(m_appContext.assetManager.GetFont()),
		("FPS: " + std::to_string(fps)).c_str(),
		Vector2(
			m_resolution.x * 0.92f,
			m_resolution.y * 0.01f),
		m_resolution.y * 0.03f,
		0.0f,
		WHITE
	);
#endif // _DEBUG

	EndDrawing();
}

void UIManager::SetWindowSize(bool full_screen) {
	std::pair<int, int> values;
	if (full_screen) {
		values = m_appContext.constants.window.GetIntFromResolution(Resolution::SCREEN);
	}
	else {
		values = m_appContext.constants.window.GetIntFromResolution(m_nextResolution);
	}

	m_resolution = { static_cast<float>(values.first), static_cast<float>(values.second) };

	::SetWindowSize(values.first, values.second);
}

void UIManager::SetWindowPosition() {
	if(IsWindowFullscreen()) { return; }

	int const screen{ GetCurrentMonitor() };
	int const screenHeight{ GetMonitorHeight(screen) };
	int const screenWidth{ GetMonitorWidth(screen) };

	int differenceWidth{ (screenWidth - static_cast<int>(m_resolution.x)) / 2 };
	int differenceHeight{ (screenHeight - static_cast<int>(m_resolution.y)) / 2 };

	if(differenceWidth < 0) { differenceWidth = 0; }
	if(differenceHeight < 0) { differenceHeight = 10; }

	::SetWindowPosition(differenceWidth, differenceHeight);
}

void UIManager::SetTargetFPS(SetTargetFPSEvent const* event) {
	::SetTargetFPS(static_cast<int>(event->GetFPS()));
	Print(
		PrintType::INFO,
		"fps set -> {}",
		event->GetFPS()
	);
}

void UIManager::UILoop() {
	while(!WindowShouldClose()) {
		m_appContext.constants.global.acceptInputTriggered = false;
		CheckAndSetNewResolution();
		CheckAndUpdate();
		Render();
		if(m_closeWindow) {
			break;
		}
	}
	CloseWindow();
}

UIManager::UIManager()
	: m_appContext(AppContext::GetInstance()), m_resolution({ 0.0f,0.0f }), m_sceneManager(this),
	m_nextResolution(Resolution::LAST) {

	SetExitKey(KeyboardKey::KEY_NULL);

	m_appContext.eventManager.AddListener(this);

	Print(PrintType::INITIALIZE, "UIManager");
}

UIManager::~UIManager() {
	m_appContext.eventManager.RemoveListener(this);
}

void UIManager::StartUI() {

	SetWindowTitle(("Tentakels Attacking " + m_appContext.constants.global.gameVersion).c_str());

	if(m_appContext.constants.window.current_resolution == Resolution::LAST) {

		m_nextResolution = Resolution::SCREEN;
		m_appContext.constants.window.current_resolution = Resolution::SCREEN;

		SetWindowSize(false);
		SetWindowPosition();

		m_sceneManager.SetResolution(m_resolution);

		ShowInitialSoundLevelPopUpEvent event{
			m_appContext.languageManager.Text("ui_manager_initial_sound_popup_title"),
			m_appContext.languageManager.Text("ui_manager_initial_sound_popup_text")
		};
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	} else {
		m_nextResolution = m_appContext.constants.window.current_resolution;

		if (!m_appContext.constants.window.IsPossibleResolution(m_nextResolution)) {
			Print(
				PrintType::ERROR,
				"invalid resolution: {} -> resolution set to: {}",
				m_appContext.constants.window.GetStringFromResolution(m_nextResolution),
				m_appContext.constants.window.GetStringFromResolution(Resolution::SCREEN)
			);
			m_nextResolution = Resolution::SCREEN;
			m_appContext.constants.window.current_resolution = Resolution::SCREEN;
		}

		SetWindowSize(false);
		m_sceneManager.SetResolution(m_resolution);
	}

	Print(PrintType::INFO, "\"UI\" started");
}

void UIManager::StartUILoop() {

	SwitchSceneEvent event{ SceneType::LOGO };
	m_appContext.eventManager.InvokeEvent(event);


	if(m_appContext.constants.window.startingModeFullScreen) {
		ToggleFullScreen(true);
	} else {
		SetWindowPosition();
	}

	Print(PrintType::INFO, "\"UI Loop\" started");

	UILoop();
}

void UIManager::OnEvent(Event const& event) {
	if(auto const* CloseEvent = dynamic_cast<CloseWindowEvent const*>(&event)) {
		m_closeWindow = true;
		return;
	}

	if(auto const* ResolutionEvent = dynamic_cast<SetNewResolutionEvent const*>(&event)) {
		m_nextResolution = ResolutionEvent->GetResolution();
	}

	if(auto const* ToggleEvent = dynamic_cast<ToggleFullscreenEvent const*>(&event)) {
		ToggleFullScreen();
		return;
	}

	if(auto const* FPSEvent = dynamic_cast<SetTargetFPSEvent const*>(&event)) {
		SetTargetFPS(FPSEvent);
		return;
	}
}

Vector2 UIManager::GetResolution() const {
	return m_resolution;
}
