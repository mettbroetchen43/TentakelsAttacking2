//
// Purpur Tentakel
// 01.10.2022
//

#include "HPrint.h"
#include "TestScene.h"
#include "SceneType.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "Table.h"



void TestScene::Initialize([[maybe_unused]] AppContext_ty appContext) {

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
		SwitchSceneEvent const event{ SceneType::MAIN_MENU };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(backBtn);
}

TestScene::TestScene(Vector2 resolution)
	: Scene{ {0.5f, 0.5f}, {1.0f, 1.0f}, Alignment::MID_MID, resolution } {

	AppContext_ty appContext{ AppContext::GetInstance() };
	Initialize(appContext);
}

void TestScene::SetActive(bool active, AppContext_ty_c appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda(bool toggled) {
	Print(
		PrintType::DEBUG,
		"toggled -> {}",
		toggled
	);
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}
void TestScene::Render(AppContext_ty_c appContext) {
	Scene::Render(appContext);
	Rectangle draw(
		m_resolution.x * 0.25f,
		m_resolution.y * 0.25f,
		m_resolution.x * 0.5f,
		m_resolution.y * 0.5f
	);
	DrawRectangleLinesEx(
		draw, 2.0f, WHITE
	);
}
void TestScene::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	Scene::Resize(resolution, appContext);
}
