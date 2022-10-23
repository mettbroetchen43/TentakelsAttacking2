//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "UIManager.h"
#include "CheckBox.h"

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {
	auto checkBox_1 = std::make_shared<CheckBox>(
		1,
		GetElementPosition(0.3f, 0.2f),
		GetElementSize(0.0f, 0.05f).y,
		Alignment::MID_MID,
		1,
		resolution
		);
	m_elements.push_back(checkBox_1);


	// to get Back No testing
	auto backBtn = std::make_shared<ClassicButton>(
		100,
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

TestScene::TestScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment) {
	Initialize(resolution, AppContext::GetInstance());
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
