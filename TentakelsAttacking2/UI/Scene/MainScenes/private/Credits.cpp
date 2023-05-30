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
#include "SceneType.h"
#include "CreditTable.h"
#include "AppContext.h"

void CreditsScene::Initialize(Vector2 resolution) {
	AppContext& appContext{ AppContext::GetInstance() };

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
	m_speedBTN->SetEnabled(false);
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
		GetElementSize(0.5f, 0.15f),
		Alignment::MID_MID,
		resolution,
		Alignment::MID_MID,
		0.15f,
		"Credits"
		);
	// creditsText->RenderRectangle(true);
	AddMovingElement(creditsText);

	auto creditsLine = std::make_shared<Line>(
		GetElementPosition(0.35f, 0.21f),
		GetElementPosition(0.65f, 0.21f),
		resolution,
		3.0f,
		WHITE
		);
	AddMovingElement(creditsLine);


	// title
	m_title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.9f, 0.4f),
		Alignment::MID_MID,
		resolution,
		true,
		appContext
		);
	AddMovingElement(m_title);

	m_titleLine = std::make_shared<Line>(
		GetElementPosition(0.05f, 0.5f),
		GetElementPosition(0.95f, 0.5f),
		resolution,
		5.0f,
		WHITE
	);
	// Added to Element when moving is true

	float Y{ 1.1f };
	float height{ 0.5f };

	auto setHeight = [&Y, &height](float newHeight, float spacing) {
		Y += height + spacing;
		height = newHeight;
	};

	// logo
	auto logo = std::make_shared<Picture>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		resolution,
		AssetType::LOGO
		);
	AddMovingElement(logo);

	setHeight(0.1f, 0.02f);
	auto logoText = std::make_shared<Text>(
		GetElementPosition(0.5f, Y),
		GetElementSize(1.0f, height),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_MID,
		0.08f,
		"A Purpur Tentakel Production"
		);
	// logoText->RenderRectangle(true);
	AddMovingElement(logoText);


	// credits vector
	// lib
	using creditEntries = std::vector<std::vector<std::string>>;
	creditEntries libVec = {
		{"raylib", "", "www.raylib.com", "https://www.raylib.com"},
		{"random lib", "", "www.github.com/mgerhold", "https://www.github.com/mgerhold"},
	};
	// inspiration
	creditEntries inspirationVec = {
		{"my Dad"},
		{"coder2k"},
	};
	// tester
	creditEntries testerVec = {
		{"Kiki3578"},
		{"TODO"},
	};
	// special thanks
	creditEntries specialThanksVec = {
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
		resolution,
		"Libraries",
		libVec,
		true
		);
	libTable->SetActive(true, appContext);
	AddMovingElement(libTable);

	setHeight(0.5f, 0.3f);
	auto inspirationTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		resolution,
		"Inspiration",
		inspirationVec
		);
	inspirationTable->SetActive(true, appContext);
	AddMovingElement(inspirationTable);

	setHeight(0.5f, 0.3f);
	auto testersTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		resolution,
		"Testers",
		testerVec
		);
	testersTable->SetActive(true, appContext);
	AddMovingElement(testersTable);

	setHeight(0.5f, 0.3f);
	auto spatialThanksTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		resolution,
		"Special Thanks",
		specialThanksVec
		);
	spatialThanksTable->SetActive(true, appContext);
	AddMovingElement(spatialThanksTable);

	setHeight(0.5f, 0.3f);
	auto contactTable = std::make_shared<CreditTableScene>(
		GetElementPosition(0.5f, Y),
		GetElementSize(0.5f, height),
		Alignment::TOP_MID,
		resolution,
		"Contact",
		contactVec,
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

	if (!m_title->HasFinishedTitle()) { return; }

	++m_speedLevel;

	if (m_speedLevel > m_maxSpeedLevel) {
		m_speedLevel = 1;
	}

	std::string text{ m_speedBTN->GetText() };
	text = text.substr(0, text.size() - 4);
	text += " " + std::to_string(m_speedLevel) + "/" + std::to_string(m_maxSpeedLevel);
	m_speedBTN->SetText(text);
	
	for (auto e : m_movingElements) {
		e->MoveBySpeed(m_speed * m_speedLevel, 0.0f);
	}

}
void CreditsScene::CheckCreditsFinished() {
	float const shouldY{ (m_resolution.y * 0.75f) - (m_finishBTN->GetCollider().height / 2) };
	float const btnY{ m_finishBTN->GetCollider().y };
	if (btnY <= shouldY) {
		for (auto& e : m_movingElements) {
			e->StopMoving();
		}
	}
}

CreditsScene::CreditsScene(Vector2 resolution)
	:Scene{ { 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution } {
	Initialize(resolution);
}

void CreditsScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	if (m_title->IsTitleFinished()) {
		m_speedBTN->SetEnabled(true);
		AddMovingElement(m_titleLine);
		for (auto& e : m_movingElements) {
			e->MoveBySpeed(m_speed * m_speedLevel, 0.0f);
		}
	}

	CheckCreditsFinished();


	// for debugging
	/*if (IsKeyPressed(KEY_ESCAPE)) {
		m_moving = !m_moving;
	}*/
}
void CreditsScene::Resize(Vector2 resolution, AppContext const& appContext) {
	m_resolution = resolution;
	Scene::Resize(resolution, appContext);
}
