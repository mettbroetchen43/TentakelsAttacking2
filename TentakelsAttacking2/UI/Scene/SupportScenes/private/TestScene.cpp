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

	m_dropDown = std::make_shared<DropDown>(
		GetElementPosition(0.5f, 0.25f),
		GetElementSize(0.25f, 0.03f),
		Alignment::TOP_MID,
		m_resolution,
		0.5f,
		1,
		10,
		m_entries
		);
	m_dropDown->SetOnSave([this](unsigned int index) {
		this->TestLambda(index);
		});
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

void TestScene::TestLambda(unsigned int value) {
	std::cout << "Index Triggert -> " << value << '\n';
	std::cout << "Value Triggert -> " << m_entries[value - 1] << '\n';
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);
}

