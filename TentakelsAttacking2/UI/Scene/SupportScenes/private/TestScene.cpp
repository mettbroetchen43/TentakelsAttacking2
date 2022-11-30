//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "UIManager.h"
#include "GameEventSettings.h"
#include <iostream>

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {

	m_settings = std::make_shared<GameEventSettings>(
		1,
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(0.5f, 0.5f),
		Alignment::TOP_LEFT,
		m_resolution
		);
	m_settings->SetActive(true, appContext);
	m_elements.push_back(m_settings);

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

	if (!m_settings->IsMoving()) {
		std::cout << m_settings->IsMoving() << " | " << m_settings->GetPosition().x << '\n';
		if (m_settings->GetPosition().x <= 0.001f) {
			m_settings->MoveToPositionAsymptotic(Vector2(0.5f, 0.5f), 2.0f);
		}
		else {
			m_settings->MoveToPositionLinear(Vector2(0.0f, 0.0f), 0.5f);
		}
	}
}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);

	DrawRectangleLinesEx(
		m_settings->GetCollider(),
		3.0f,
		WHITE
	);

	auto col = m_settings->GetCollider();
	DrawLine(
		col.x + col.width / 2,
		col.y,
		col.x + col.width / 2,
		col.y + col.height,
		WHITE
	);
}

