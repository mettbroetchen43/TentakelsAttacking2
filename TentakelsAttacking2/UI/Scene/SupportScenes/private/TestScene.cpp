//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "UIManager.h"
#include "GalaxyAndSlider.h"
#include <iostream>

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {

	auto galaxyScene = std::make_shared<GalaxyScene>(
		GetElementPosition(0.05f, 0.05f),
		GetElementSize(0.7f, 0.7f),
		Alignment::TOP_LEFT,
		resolution
		);
	galaxyScene->SetActive(true, appContext);
	m_elements.push_back(galaxyScene);

	auto galaxyPos = GetElementPosition(0.05f, 0.05f);
	auto galaxySize = GetElementSize(0.7f, 0.7f);
	m_coldier = {
		galaxyPos.x * resolution.x,
		galaxyPos.y * resolution.y,
		galaxySize.x * resolution.x,
		galaxySize.y * resolution.y,
	};

	// to get Back No testing
	auto backBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.05f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		resolution,
		"Back",
		SoundType::CLICKED_PRESS_STD
		);
	backBtn->SetOnClick([]() {
		auto event = SwitchSceneEvent(SceneType::MAIN_MENU);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(backBtn);
}

TestScene::TestScene(Vector2 resolution)
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT), m_resolution(resolution) {
	Initialize(resolution, AppContext::GetInstance());
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda(float value) {
	std::cout << "Value Triggert -> " << value << '\n';
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);
	
	DrawRectangleLinesEx(
		m_coldier,
		3.0f,
		PURPLE
	);
}

