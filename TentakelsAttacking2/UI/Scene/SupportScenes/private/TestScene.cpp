//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "ClassicButton.h"
#include "SceneType.h"
#include "DropDown.h"
#include <iostream>

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {

	std::vector<std::string> entries = {
		"Eintrag 1",
		"Eintrag 2",
		"Eintrag 3",
		"Eintrag 4",
		"Eintrag 5",
		"Eintrag 6",
		"Eintrag 7",
		"Eintrag 9",
		"Eintrag 10",
		"Eintrag 11",
		"Eintrag 12",
		"Eintrag 13",
		"Eintrag 14",
		"Eintrag 15",
		"Eintrag 16",
		"Eintrag 17",
		"Eintrag 18",
		"Eintrag 19",
		"Eintrag 20",
		"Eintrag 21",
		"Eintrag 22",
		"Eintrag 23",
		"Eintrag 24",
		"Eintrag 25",
		"Eintrag 26",
		"Eintrag 27",
		"Eintrag 28",
		"Eintrag 29",
		"Eintrag 30",
		"Eintrag 31",
		"Eintrag 32",
		"Eintrag 33",
		"Eintrag 34",
		"Eintrag 35",
		"Eintrag 36",
		"Eintrag 37",
		"Eintrag 38",
		"Eintrag 39",
	};

	m_dropDown = std::make_shared<DropDown>(
		GetElementPosition(0.5f, 0.25f),
		GetElementSize(0.25f, 0.03f),
		Alignment::TOP_MID,
		m_resolution,
		0.5f,
		1,
		10,
		entries
		);
	m_elements.push_back(m_dropDown);

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
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT, resolution) {
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
}

