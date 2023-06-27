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

	m_first = std::make_shared<CountingNumber>(
		GetElementPosition(0.25f + 0.16f, 0.5f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		0.1f,
		1000
	);
	m_first->SetCallback([this](CountingNumber::Type type, int start, int current, double time) {
		this->TestLambda(type, start, current, time);
		});
	m_elements.push_back(m_first);

	m_second = std::make_shared<CountingNumber>(
		GetElementPosition(0.75f - 0.16f, 0.5f),
		GetElementSize(0.2f, 0.1f),
		Alignment::MID_MID,
		m_resolution,
		Alignment::MID_MID,
		0.1f,
		1000
	);
	m_second->SetCallback([this](CountingNumber::Type type, int start, int current, double time) {
		this->TestLambda(type, start, current, time);
		});
	m_elements.push_back(m_second);

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

void TestScene::TestLambda(CountingNumber::Type type, int start, int current, double time) {
	if (type == CountingNumber::LINEAR) { return; }
	std::stringstream ss;
	ss << "type: " << type << " | start: " << start << " | current: " << current << " | time: " << time;
	Print(ss.str(), PrintType::DEBUG);
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	auto const nextNumberAndTime{ [&]() -> std::pair<int, double> {
		int index{static_cast<int>(m_random.random(m_numbers.size()))};
		int const number{ m_numbers.at(index) };

		index = { static_cast<int>(m_random.random(m_times.size())) };
		double const time{ m_times.at(index) };

		return { number, time };
	} };

	if (not m_first->IsCounting()) {
		auto const [number, time] {nextNumberAndTime()};
		m_first->CountTo(CountingNumber::LINEAR, number, time);
		std::stringstream ss;
		ss << "type: " << CountingNumber::LINEAR << " | number: " << number << " | time: " << time;
		// Print(ss.str(), PrintType::DEBUG);
	}
	if (not m_second->IsCounting()) {
		auto const [number, time] {nextNumberAndTime()};
		m_second->CountTo(CountingNumber::ASYMPTOTIC, number, time);
		std::stringstream ss;
		ss << "type: " << CountingNumber::ASYMPTOTIC << " | number: " << number << " | time: " << time;
		Print(ss.str(), PrintType::DEBUG);
	}
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
