//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "ClassicButton.h"
#include "SceneType.h"
#include "AppContext.h"
#include "Table2.h"
#include <iostream>

void TestScene::Initialize(	[[maybe_unused]] AppContext& appContext) {

	auto table = std::make_shared<Table2>(
		Vector2(0.5f, 0.5f), // pos
		Vector2(0.5f, 0.5f), // size
		Alignment::MID_MID,
		m_resolution,
		1, // focus ID
		5, // row count
		6, // column count
		Vector2(0.2f, 0.1f) // min cell size
	);
	m_elements.push_back(table);

	table->SetRowEditable(2, false);
	table->SetColumnEditable(1, false);

	// to get Back No testing
	auto backBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.05f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
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
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT, resolution) {

	AppContext& appContext = AppContext::GetInstance();
	Initialize(appContext);
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda([[maybe_unused]] unsigned int value) {
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);
}

void TestScene::OnEvent(Event const& event) {
	if (auto const* galaxyEvent = dynamic_cast<SendGalaxyPointerEvent const*>(&event)) {
		Initialize(AppContext::GetInstance());
	}
}

