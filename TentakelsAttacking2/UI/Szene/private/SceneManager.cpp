

#include "SceneManager.h"
#include "Scene.h"
#include "TestScene.h"
#include "UIManager.h"
#include "AppContext.h"
#include <raylib.h>

void SceneManager::InitializeScenes() {
	auto ptr = std::make_shared<TestScene>(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), true, *m_uiManager);
	m_scenes[SceneType::TEST] = ptr;
}

SceneManager::SceneManager(UIManager* uiManager)
	: m_uiManager(uiManager){
	InitializeScenes();
}

void SceneManager::SwitchScene(SceneType sceneType) {
	auto& focus = m_uiManager->GetFocus();

	if (m_currentScene) {
		m_currentScene->SetActive(false, focus);
	}
	m_currentScene = m_scenes.at(sceneType);
	m_currentScene->SetActive(true, focus);
}

void SceneManager::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	m_currentScene->CheckAndUpdate(mousePosition, appContext);
}
void SceneManager::Render() {
	m_currentScene->Render();
}
void SceneManager::Resize(Vector2 resolution) {
	for (auto [sceneType, scene] : m_scenes) {
		scene->Resize(resolution);
	}
}
