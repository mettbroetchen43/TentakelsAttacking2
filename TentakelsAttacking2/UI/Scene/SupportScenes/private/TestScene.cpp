//
// Purpur Tentakel
// 01.10.2022
//

#include "TestScene.h"
#include "ClassicButton.h"
#include "SceneType.h"
#include "AppContext.h"
#include "Text.h"
#include <iostream>

void TestScene::Initialize(Vector2 resolution,
	[[maybe_unused]] AppContext& appContext) {

	auto input = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet.";

	auto text = std::make_shared<Text>(
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(0.33f, 0.33f),
		Alignment::TOP_LEFT,
		m_resolution,
		Alignment::TOP_LEFT,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.0f),
		GetElementSize(0.33f, 0.33f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(1.0f, 0.0f),
		GetElementSize(0.33f, 0.33f),
		Alignment::TOP_RIGHT,
		m_resolution,
		Alignment::TOP_RIGHT,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(0.0f, 0.5f),
		GetElementSize(0.33f, 0.33f),
		Alignment::MID_LEFT,
		m_resolution,
		Alignment::MID_LEFT,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.33f, 0.33f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(1.0f, 0.5f),
		GetElementSize(0.33f, 0.33f),
		Alignment::MID_RIGHT,
		m_resolution,
		Alignment::MID_RIGHT,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(0.0f, 1.0f),
		GetElementSize(0.33f, 0.33f),
		Alignment::BOTTOM_LEFT,
		m_resolution,
		Alignment::BOTTOM_LEFT,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(0.5f, 1.0f),
		GetElementSize(0.33f, 0.33f),
		Alignment::BOTTOM_MID,
		m_resolution,
		Alignment::BOTTOM_MID,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);

	text = std::make_shared<Text>(
		GetElementPosition(1.0f, 1.0f),
		GetElementSize(0.33f, 0.33f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.025f,
		input
		);
	text->RenderRectangle(true);
	text->LineBreaks(true);
	m_elements.push_back(text);


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

	AppContext &appContext = AppContext::GetInstance ( );

	Initialize(resolution, appContext );
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

