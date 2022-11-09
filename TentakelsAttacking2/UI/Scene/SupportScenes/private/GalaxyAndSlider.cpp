//
// Purpur Tentakel
// 09.11.2022
//

#include "GalaxyAndSlider.h"
#include "GenerelEvents.hpp"
#include "Slider.h"
#include "ClassicButton.h"

void GalaxyScene::Initialize() {

	// slider
	m_verticalSlider = std::make_shared<Slider>(
		GetElementPosition(0.00f, 0.46f),
		GetElementSize(0.03f, 0.5f),
		Alignment::MID_LEFT,
		false,
		10.0f,
		m_resolution
		);
	m_verticalSlider->SetScrolling(true);
	m_elements.push_back(m_verticalSlider);

	m_horisontalSlider = std::make_shared<Slider>(
		GetElementPosition(0.5175f, 1.0f),
		GetElementSize(0.5f, 0.05f),
		Alignment::BOTTOM_MID,
		true,
		10.0f,
		m_resolution
		);
	m_horisontalSlider->SetScrolling(true);
	m_elements.push_back(m_horisontalSlider);

	// Btn
	m_zoomInBtn = std::make_shared<ClassicButton>(
		100,
		GetElementPosition(1.0f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		"+",
		SoundType::CLICKED_RELEASE_STD
		);
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
	m_elements.push_back(m_zoomOutBtn);

	// Galaxy
	auto galaxyPos = GetElementPosition(0.035f, 0.0f);
	auto galaxySize = GetElementSize(0.965f, 0.94f);
	m_galaxyColider = {
		galaxyPos.x * m_resolution.x,
		galaxyPos.y * m_resolution.y,
		galaxySize.x * m_resolution.x,
		galaxySize.y * m_resolution.y
	};
}

void GalaxyScene::UpdateGalaxy() {}

GalaxyScene::GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment), m_resolution(resolution) {
	GetAlignedCollider(m_pos, m_size, alignment, m_resolution);
	Initialize();
}

void GalaxyScene::OnEvent(Event const& event) {

	if (auto const* GalaxyEvent = dynamic_cast<SendGalaxyCopy const*>(&event)) {
		m_currentGalaxy = GalaxyEvent->GetGalaxy();
		UpdateGalaxy();
		return;
	}
}

void GalaxyScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);

	DrawRectangleLinesEx(
		m_galaxyColider,
		3.0f,
		WHITE
	);
}
