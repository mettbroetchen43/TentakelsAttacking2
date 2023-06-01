//
// Purpur Tentakel
// 01.10.2022
//

#include "HPrint.h"
#include "TestScene.h"
#include "SceneType.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "LineDrag.h"



void TestScene::Initialize([[maybe_unused]] AppContext& appContext) {

	auto line = std::make_shared<LineDrag>(
		m_resolution,
		2.0f,
		WHITE,
		[this](Vector2 start, Vector2 end) {
			this->LineCallBack(start, end);
		}
	);
	m_elements.push_back(line);

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
	: Scene{ {0.5f, 0.5f}, {0.75f, 0.75f}, Alignment::MID_MID, resolution } {

	AppContext& appContext{ AppContext::GetInstance() };
	Initialize(appContext);
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda([[maybe_unused]] unsigned int value) { }

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}

void TestScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);
	DrawRectangleLinesEx(
		m_collider,
		2.0f,
		WHITE
	);
}

void TestScene::LineCallBack(Vector2 start, Vector2 end) {
	Vector2 const elementStart = {
		GetElementPositionReversed(m_pos, m_size, start)
	};
	Vector2 const elementEnd = {
		GetElementPositionReversed(m_pos,m_size,end)
	};
	Print("Callback global  relative -> start: " + ToString(start)        + " | end: " + ToString(end),        PrintType::DEBUG);
	Print("Callback element relative -> start: " + ToString(elementStart) + " | end: " + ToString(elementEnd), PrintType::DEBUG);
}
