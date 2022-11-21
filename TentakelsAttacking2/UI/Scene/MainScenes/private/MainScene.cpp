//
// Purpur Tentakel
// 21.11.2022
//

#include "MainScene.h"
#include "GalaxyAndSlider.h"
#include "AppContext.h"
#include "ClassicButton.h"
#include "Title.h"

void MainScene::Initialize() {

	// Title
	auto title = std::make_shared<Title>(
		GetElementPosition(0.31f, 0.0f),
		GetElementSize(0.6f, 0.2f),
		Alignment::TOP_MID,
		m_resolution,
		false,
		AppContext::GetInstance()
		);
	m_elements.push_back(title);

	// Btn
	auto settingsBtn = std::make_shared<ClassicButton>(
		5,
		GetElementPosition(0.95f, 0.02f),
		GetElementSize(0.05f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"settings",
		SoundType::CLICKED_RELEASE_STD
		);
	m_elements.push_back(settingsBtn);


	auto galaxyBtn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.7f, 0.02f),
		GetElementSize(0.1f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"galaxy",
		SoundType::CLICKED_RELEASE_STD
		);
	galaxyBtn->SetOnClick([this]() {
		this->Switch(MainSceneType::GALAXY);
		});
	m_elements.push_back(galaxyBtn);

	auto planetTableBtn = std::make_shared<ClassicButton>(
		2,
		GetElementPosition(0.8f, 0.02f),
		GetElementSize(0.1f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"planet table",
		SoundType::CLICKED_RELEASE_STD
		);
	planetTableBtn->SetOnClick([this]() {
		this->Switch(MainSceneType::PLANET_TABLE);
		});
	m_elements.push_back(planetTableBtn);

	auto fleetTableBtn = std::make_shared<ClassicButton>(
		3,
		GetElementPosition(0.9f, 0.02f),
		GetElementSize(0.1f, 0.05f),
		Alignment::TOP_RIGHT,
		m_resolution,
		"fleet table",
		SoundType::CLICKED_RELEASE_STD
		);
	fleetTableBtn->SetOnClick([this]() {
		this->Switch(MainSceneType::FLEET_TABLE);
		});
	m_elements.push_back(fleetTableBtn);

	auto nextBtn = std::make_shared<ClassicButton>(
		4,
		GetElementPosition(0.95f, 0.95f),
		GetElementSize(0.1f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"next",
		SoundType::ACCEPTED
		);
	nextBtn->SetOnClick([this]() {
		this->InitialzeGalaxy();
		});
	m_elements.push_back(nextBtn);
}
void MainScene::InitialzeGalaxy() {
	AppContext& appContext = AppContext::GetInstance();
	if (m_galaxy) {
		m_galaxy->SetActive(false, appContext);
		m_elements.erase(std::remove(m_elements.begin(), m_elements.end(), m_galaxy), m_elements.end());
		m_galaxy = nullptr;
	}

	m_galaxy = std::make_shared<GalaxyScene>(
		GetElementPosition(0.5f, 0.5f),
		GetElementSize(0.75f, 0.75f),
		Alignment::MID_MID,
		m_resolution
		);
	m_galaxy->SetActive(true, appContext);
	m_elements.push_back(m_galaxy);
}

void MainScene::Switch(MainSceneType sceneType) {
	AppContext& appContext = AppContext::GetInstance();

	m_galaxy->SetActive(sceneType == MainSceneType::GALAXY, appContext);
	// m_planetTable->SetActive(sceneType == MainSceneType::PLANET_TABLE, appContext);
	// m_fleetTable->SetActive(sceneType == MainSceneType::FLEET_TABLE, appContext);
}

MainScene::MainScene(Vector2 resolution)
	: Scene({ 0.0f,0.0f }, { 1.0f,1.0f }, Alignment::DEFAULT, resolution) {

	Initialize();
	InitialzeGalaxy();
}
