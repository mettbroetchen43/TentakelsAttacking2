//
// Purpur Tentakel
// 01.10.2022
//

#include "HPrint.h"
#include "TestScene.h"
#include "SceneType.h"
#include "AppContext.h"
#include "ExpandingButton.h"
#include "ClassicButton.h"
#include "Table.h"

void TestScene::Initialize([[maybe_unused]] AppContext_ty appContext) {

	auto mainBtn = std::make_shared<ExpandingButton>(
		1,
		GetElementPosition(0.5f,0.5f),
		GetElementSize(0.2f,0.1f),
		Alignment::MID_MID,
		m_resolution,
		ExpandingButton::UP,
		0.01f,
		10.0f,
		"main button"
	);
	m_elements.push_back(mainBtn);

	auto firstBtn = std::make_shared<ClassicButton>(
		2,
		Vector2(0.0f,0.0f),
		Vector2(0.0f,0.0f),
		Alignment::DEFAULT,
		m_resolution,
		"first expanding",
		SoundType::CLICKED_RELEASE_STD
	);
	mainBtn->Add(firstBtn, true);

	auto secondBtn = std::make_shared<ClassicButton>(
		3,
		Vector2(0.0f,0.1f),
		Vector2(0.0f,0.0f),
		Alignment::DEFAULT,
		m_resolution,
		"second expanding",
		SoundType::CLICKED_RELEASE_STD
	);
	mainBtn->Add(secondBtn, false);

	auto thirdBtn = std::make_shared<ClassicButton>(
		4,
		Vector2(0.0f,0.2f),
		Vector2(0.0f,0.0f),
		Alignment::DEFAULT,
		m_resolution,
		"third expanding",
		SoundType::CLICKED_RELEASE_STD
	);
	mainBtn->Add(thirdBtn, true);
	mainBtn->Update();

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
}
void TestScene::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	Scene::Resize(resolution, appContext);
}
