//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "UIManager.h"
#include "SliderAndInputLine.h"
#include <iostream>

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {
	
	float position = 0.3f;
	for (int i = 100; i < 105; i +=2) {
		auto scene = std::make_shared<SliderAndInputLine>(
			i,
			GetElementPosition(0.5f, position),
			GetElementSize(0.3f, 0.03f),
			Alignment::MID_MID,
			0,
			100,
			61,
			resolution
			);
		scene->SetActive(true, appContext);
		scene->SetOnSave([this](int value) {
			TestLambda(value);
			});
		m_elements.push_back(scene);
		position += 0.05f;
	}


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
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT) {
	Initialize(resolution, AppContext::GetInstance());
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda(int value) {
	std::cout << "Value Triggert -> " << value << '\n';
}
