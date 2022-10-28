//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "UIManager.h"
#include "Slider.h"
#include <iostream>

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {

	auto hSlider_1 = std::make_shared<Slider>(
		GetElementPosition(0.5f, 0.1f),
		GetElementSize(0.5f, 0.05f),
		Alignment::TOP_MID,
		true,
		10.0f,
		resolution
		);
	hSlider_1->SetScrolling(true);
	hSlider_1->SetOnSlide([this](float value) {
		this->TestLambda(value);
		});
	m_elements.push_back(hSlider_1);

	auto hSlider_2 = std::make_shared<Slider>(
		GetElementPosition(0.5f, 0.85f),
		GetElementSize(0.5f, 0.05f),
		Alignment::TOP_MID,
		true,
		10.0f,
		resolution
		);
	hSlider_2->SetOnSlide([this](float value) {
		this->TestLambda(value);
		});
	m_elements.push_back(hSlider_2);


	auto vSlider_1 = std::make_shared<Slider>(
		GetElementPosition(0.1f, 0.5f),
		GetElementSize(0.05f, 0.5f),
		Alignment::MID_LEFT,
		false,
		10.0f,
		resolution
		);
	vSlider_1->SetScrolling(true);
	vSlider_1->SetOnSlide([this](float value) {
		this->TestLambda(value);
		});
	m_elements.push_back(vSlider_1);

	auto vSlider_2 = std::make_shared<Slider>(
		GetElementPosition(0.85f, 0.5f),
		GetElementSize(0.05f, 0.5f),
		Alignment::MID_LEFT,
		false,
		10.0f,
		resolution
		);
	vSlider_2->SetOnSlide([this](float value) {
		this->TestLambda(value);
		});
	m_elements.push_back(vSlider_2);

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
	: Scene(Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), Alignment::DEFAULT) {
	Initialize(resolution, AppContext::GetInstance());
}

void TestScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda(float value) {
	std::cout << "Value Triggert -> " << value << '\n';
}
