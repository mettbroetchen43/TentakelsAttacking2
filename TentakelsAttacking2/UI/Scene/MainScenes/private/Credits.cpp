//
// Purpur Tentakel
// 04.11.2022
//

#include "Credits.h"
#include "Title.h"
#include "Text.h"
#include "Line.h"
#include "Picture.h"
#include "ClassicButton.h"
#include "SceneType.hpp"
#include "CreditTable.h"
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

	m_titleLine = std::make_shared<Line>(
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.9f, 0.0f),
		Alignment::MID_MID,
		5.0f,
		resolution
		);
	// Added to Element when moving is true

	float Y = 1.1f;
	float height = 0.5f;

	auto setHeight = [&Y, &height](float newHeight, float spacing) {
		Y += height + spacing;
		height = newHeight;
	};

	// logo
	auto logo = std::make_shared<Picture>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		AssetType::LOGO,
		resolution
		);
	AddMovingElement(logo);

	setHeight(0.1f, 0.02f);
	auto logoText = std::make_shared<Text>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.08f,
		"A Purpur Tentakel Production",
		resolution
		);
	AddMovingElement(logoText);


	// credits vector
	// lib
	using creditEntries = std::vector<std::vector<std::string>>;
	creditEntries libVec = {
		{"raylib", "", "www.raylib.com", "https://www.raylib.com"},
		{"random lib", "", "www.github.com/mgerhold", "https://www.github.com/mgerhold"},
	};
	// inperation
	creditEntries inspreationVec = {
		{"my Dad"},
		{"coder2k"},
	};
	// tester
	creditEntries testerVec = {
		{"TODO"},
	};
	// special thanks
	creditEntries specialThancsVec = {
		{"coder2k"},
		{"r00tifant"},
		{"Clemens"},
		{"CrazyNightowl01"},
		{"NECROMENZER"},
		{"german coding commuinty on twitch"},
		{"the discord of coder2k"},
		{"TODO: more to come"},
	};
	// contact
	creditEntries contactVec = {
		{"discord", "", "www.discord.gg/JG5fsFZqEE", "https://www.discord.gg/JG5fsFZqEE"},
		{"twitch", "", "www.twitch.tv/codingPurpurTentakel", "https://www.twitch.tv/codingpurpurtentakel"},
		{"gitHub", "", "www.github.com/PurpurTentakel97", "https://www.github.com/PurpurTentakel97"},
	};

	// credits table
	setHeight(0.5f, 0.5f);
	auto libTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		"Libraries",
		libVec,
		resolution,
		true
		);
	libTable->SetActive(true, appContext);
	AddMovingElement(libTable);

	setHeight(0.5f, 0.3f);
	auto inspirationTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		"Inspiration",
		inspreationVec,
		resolution
		);
	inspirationTable->SetActive(true, appContext);
	AddMovingElement(inspirationTable);

	setHeight(0.5f, 0.3f);
	auto testersTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		"Testers",
		testerVec,
		resolution
		);
	testersTable->SetActive(true, appContext);
	AddMovingElement(testersTable);

	setHeight(0.5f, 0.3f);
	auto spacialThanksTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		"Special Thanks",
		specialThancsVec,
		resolution
		);
	spacialThanksTable->SetActive(true, appContext);
	AddMovingElement(spacialThanksTable);

	setHeight(0.5f, 0.3f);
	auto contactTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		"Contact",
		contactVec,
		resolution,
		true
		);
	contactTable->SetActive(true, appContext);
	AddMovingElement(contactTable);


	// finish btn
	setHeight(0.1f, 0.0f);
	m_finishBTN = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.5f, Y),
		GetElementSize(0.15f, height),
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
		e->SetPosition(position);
	}

}
void CreditsScene::CheckCreditsFinished() {
	float shoudY = (m_resolution.y * 0.75f) - (m_finishBTN->GetCollider().height / 2);
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
		AddMovingElement(m_titleLine);
	}

	if (m_moving) {
		Move();
		CheckCreditsFinished();
	}

	// for debugging
	/*if (IsKeyPressed(KEY_ESCAPE)) {
		m_moving = !m_moving;
	}*/
}
void CreditsScene::Resize(Vector2 resolution, AppContext const& appContext) {
	m_resolution = resolution;
	Scene::Resize(resolution, appContext);
}
