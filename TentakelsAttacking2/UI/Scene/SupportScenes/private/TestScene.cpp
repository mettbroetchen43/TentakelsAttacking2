//
// Purpur Tentakel
// 01.10.2022
//

#include "HPrint.h"
#include "TestScene.h"
#include "SceneType.h"
#include "AppContext.h"
#include "ClassicButton.h"



void TestScene::Initialize(	[[maybe_unused]] AppContext& appContext) {

	m_hover = std::make_shared<Hover>(
		0.1f,
		"Test text",
		Vector2(0.01f, 0.01f),
		m_resolution
	);
	m_elements.push_back(m_hover);
	

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
	CheckHover(mousePosition, appContext);
}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);
	RenderRectangle(appContext);

}

void TestScene::RenderRectangle(AppContext const& appContext) {
	DrawRectangleLinesEx(
		m_toRender,
		3.0f,
		WHITE
	);
}

void TestScene::CheckHover(Vector2 const& mousePosition, AppContext const& appContext) {
	if (CheckCollisionPointRec(mousePosition, m_toRender)) {
		m_hover->SetRenderHover(mousePosition, appContext);
	}
}

