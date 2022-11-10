//
// Purpur Tentakel
// 09.11.2022
//

#include "GalaxyAndSlider.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "Slider.h"
#include "Galaxy.h"
#include "PlanetUI.h"
#include "ClassicButton.h"
#include <iostream>

void GalaxyScene::Initialize() {
	AppContext& appContext = AppContext::GetInstance();

	// slider
	m_verticalSlider = std::make_shared<Slider>(
		GetElementPosition(0.00f, 0.46f),
		GetElementSize(0.03f, 0.5f),
		Alignment::MID_LEFT,
		false,
		1.7f,
		m_resolution
		);
	m_verticalSlider->SetScrolling(true);

	m_horisontalSlider = std::make_shared<Slider>(
		GetElementPosition(0.5175f, 1.0f),
		GetElementSize(0.5f, 0.05f),
		Alignment::BOTTOM_MID,
		true,
		10.0f,
		m_resolution
		);
	m_horisontalSlider->SetScrolling(true);

	// btn
	m_zoomInBtn = std::make_shared<ClassicButton>(
		100,
		GetElementPosition(1.0f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"+",
		SoundType::CLICKED_RELEASE_STD
		);
	m_zoomInBtn->SetOnPress([this]() {
		this->SetScale(true);
		});
	m_elements.push_back(m_zoomInBtn);

	m_zoomOutBtn = std::make_shared<ClassicButton>(
		101,
		GetElementPosition(0.95f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"-",
		SoundType::CLICKED_RELEASE_STD
		);
	m_zoomOutBtn->SetOnPress([this]() {
		this->SetScale(false);
		});
	m_elements.push_back(m_zoomOutBtn);

	// Galaxy
	auto event = GetGalaxyCopy();
	appContext.eventManager.InvokeEvent(event);
}

void GalaxyScene::InitialGalaxy() {
	AppContext& appContext = AppContext::GetInstance();
	m_scaleFacor = 1.0f;

	auto galaxyPos = GetElementPosition(0.035f, 0.0f);
	auto galaxySize = GetElementSize(0.965f, 0.94f);
	m_galaxyColiderDraw = {
		galaxyPos.x * m_resolution.x,
		galaxyPos.y * m_resolution.y,
		galaxySize.x * m_resolution.x,
		galaxySize.y * m_resolution.y
	};

	float offsetX = 50;
	float offsetY = 35;

	m_galaxyColider = {
		m_galaxyColiderDraw.x - offsetX,
		m_galaxyColiderDraw.y - offsetY,
		m_galaxyColiderDraw.width - 2 * offsetX,
		m_galaxyColiderDraw.height - 2 * offsetY,
	};

	float scalingFactorX = m_galaxyColider.width / m_currentGalaxy->GetSize().x;
	float scalingFactorY = m_galaxyColider.height / m_currentGalaxy->GetSize().y;
	float dummyScaling = scalingFactorX > scalingFactorY ? scalingFactorY : scalingFactorX;

	for (auto const& p : m_currentGalaxy->GetPlanets()) {

		auto color = appContext.playerCollection.GetColorByID(p->GetID());

		auto position = p->GetPos();
		auto planet = std::make_shared<PlanetUI>(
			GetElementPosition(
				position.x * dummyScaling / m_colider.width
					+ 0.035f * m_size.x
					+ offsetX / m_colider.width,
				position.y * dummyScaling / m_colider.height
					+ offsetY / m_colider.height
			),
			p->GetID(),
			color,
			m_resolution
			);

		m_galaxyElements.push_back(planet);
	}
}
void GalaxyScene::UpdateGalaxy() {
	AppContext& appContext = AppContext::GetInstance();

}

void GalaxyScene::SetScale(bool scaleIn) {
	if (scaleIn) { m_scaleFacor += 0.01f; }
	else { m_scaleFacor -= 0.01f; }

	if (m_scaleFacor < 1.0f) { m_scaleFacor = 1.0f; }

	m_horisontalSlider->SetAboluteDimension(m_scaleFacor);
	m_verticalSlider->SetAboluteDimension(m_scaleFacor);

	std::cout << m_scaleFacor << '\n';
}

GalaxyScene::GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment), m_resolution(resolution) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, m_resolution);

	AppContext::GetInstance().eventManager.AddListener(this);

	Initialize();
}
GalaxyScene::~GalaxyScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void GalaxyScene::OnEvent(Event const& event) {

	if (auto const* GalaxyEvent = dynamic_cast<SendGalaxyCopy const*>(&event)) {
		m_currentGalaxy = GalaxyEvent->GetGalaxy();
		InitialGalaxy();
		return;
	}
}

void GalaxyScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
		float mouse = GetMouseWheelMove();
		if (mouse != 0.0f) {
			SetScale(mouse > 0);
			SetScale(mouse > 0);
		}
	}

	if (m_scaleFacor > 1.0f) {
		m_horisontalSlider->CheckAndUpdate(mousePosition, appContext);
		m_verticalSlider->CheckAndUpdate(mousePosition, appContext);
	}

	for (auto& e : m_galaxyElements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}
void GalaxyScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);

	for (auto& e : m_galaxyElements) {
		e->Render(appContext);
	}

	if (m_scaleFacor > 1.0f) {
		m_horisontalSlider->Render(appContext);
		m_verticalSlider->Render(appContext);
	}

	/*DrawRectangleLinesEx(
		m_galaxyColiderDraw,
		3.0f,
		WHITE
	);*/
}