//
// Purpur Tentakel
// 04.11.2022
//

#include "Credits.h"
#include "Title.h"
#include "Text.h"
#include "Line.h"
#include "ClassicButton.h"
#include "SceneType.hpp"
#include "AppContext.h"

void CreditsScene::Initialize(Vector2 resolution) {
	AppContext& appContext = AppContext::GetInstance();

	// not moving btn
	m_speedBTN = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"Speed " + std::to_string(m_speedLevel) + "/" + std::to_string(m_maxSpeedLevel),
		SoundType::CLICKED_RELEASE_STD
		);
	m_speedBTN->SetOnClick([this]() {
		this->ToggleSpeedLevel();
		});
	m_elements.push_back(m_speedBTN);

	auto backBTN = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(0.05f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		resolution,
		"Back",
		SoundType::CLICKED_RELEASE_STD
		);
	backBTN->SetOnClick([]() {
		auto event = SwitchSceneEvent(SceneType::MAIN_MENU);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(backBTN);


	// credits
	auto creditsText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.15f),
		GetElementSize(0.25f, 0.15f),
		Alignment::MID_MID,
		Alignment::MID_MID,
		0.15f,
		"Credits",
		resolution
		);
	AddMovingElement(creditsText);

	auto creditsLine = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.21f),
		GetElementSize(0.21f, 0.0f),
		Alignment::MID_MID,
		3.0f,
		resolution
		);
	AddMovingElement(creditsLine);


	// title
	m_title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.9f, 0.4f),
		Alignment::MID_MID,
		true,
		resolution,
		appContext
		);
	AddMovingElement(m_title);


	// finish btn
	m_finishBTN = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.5f, 1.1f),
		GetElementSize(0.15f, 0.1f),
		Alignment::TOP_MID,
		resolution,
		"Finish",
		SoundType::ACCEPTED
		);
	m_finishBTN->SetOnClick([]() {
		auto event = SwitchSceneEvent(SceneType::MAIN_MENU);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	AddMovingElement(m_finishBTN);
}

void CreditsScene::AddMovingElement(std::shared_ptr<UIElement> element) {
	m_elements.push_back(element);
	m_movingElements.push_back(element);
}

void CreditsScene::ToggleSpeedLevel() {
	++m_speedLevel;

	if (m_speedLevel > m_maxSpeedLevel) {
		m_speedLevel = 1;
	}

	std::string text = m_speedBTN->GetText();
	text = text.substr(0, text.size() - 4);
	text += " " + std::to_string(m_speedLevel) + "/" + std::to_string(m_maxSpeedLevel);
	m_speedBTN->SetText(m_resolution, text);
	
}
void CreditsScene::Move() {

	if (!m_moving) { return; }

	for (auto& e : m_movingElements) {
		auto position = e->GetPosition();
		position.y += (m_speed * m_speedLevel);
		e->SetPosition(position, m_resolution);
	}

}
void CreditsScene::CheckCreditsFinished() {
	float shoudY = (m_resolution.y * 0.5f) - (m_finishBTN->GetCollider().height / 2);
	float btnY = m_finishBTN->GetCollider().y;
	if (btnY <= shoudY) {
		m_moving = false;
	}
}

CreditsScene::CreditsScene(Vector2 resolution)
	:Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT), m_resolution(resolution) {
	Initialize(resolution);
}

void CreditsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
	
	if (m_title->IsTitleFinished()) {
		m_moving = true;
	}

	if (m_moving) {
		Move();
		CheckCreditsFinished();
	}
}
void CreditsScene::Resize(Vector2 resolution, AppContext const& appContext) {
	m_resolution = resolution;
	Scene::Resize(resolution, appContext);
}
