//
// Purpur Tentakel
// 01.10.2022
//

#include "HPrint.h"
#include "TestScene.h"
#include "SceneType.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "Arrow.h"



void TestScene::Initialize(	[[maybe_unused]] AppContext_ty appContext) {
	// TL
	auto arrow = std::make_shared<Arrow>(
		GetElementPosition(0.02f, 0.02f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// TM
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.35f, 0.02f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_MID,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// TR
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.68f, 0.02f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_RIGHT,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// ML
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.02f, 0.35f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::MID_LEFT,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// MM not valid

	// MR
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.68f, 0.35f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::MID_RIGHT,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// BL
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.02f, 0.68f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::BOTTOM_LEFT,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// BM
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.35f, 0.68f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::BOTTOM_MID,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);

	// BR
	arrow = std::make_shared<Arrow>(
		GetElementPosition(0.68f, 0.68f),
		GetElementSize(0.3f, 0.3f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		WHITE,
		3.0f
	);
	m_elements.push_back(arrow);
	
	

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
	: Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, Alignment::DEFAULT, resolution } {

	AppContext_ty appContext{ AppContext::GetInstance() };
	Initialize(appContext);
}

void TestScene::SetActive(bool active, AppContext_ty_c appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda([[maybe_unused]] unsigned int value) { }

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}

void TestScene::Render(AppContext_ty_c appContext) {
	Scene::Render(appContext);
}
