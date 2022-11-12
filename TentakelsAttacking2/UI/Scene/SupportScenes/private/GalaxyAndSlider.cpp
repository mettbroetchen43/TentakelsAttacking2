//
// Purpur Tentakel
// 09.11.2022
//

#include "GalaxyAndSlider.h"
#include "AppContext.h"
#include "GenerelEvents.hpp"
#include "Slider.h"
#include "UIGalaxy.h"
#include "ClassicButton.h"

void GalaxyScene::Initialize(Vector2 resolution) {
	AppContext& appContext = AppContext::GetInstance();

	// slider
	m_verticalSlider = std::make_shared<Slider>(
		GetElementPosition(0.00f, 0.46f),
		GetElementSize(0.03f, 0.5f),
		Alignment::MID_LEFT,
		false,
		m_galaxayScaleFacor,
		resolution
		);
	m_verticalSlider->SetScrolling(true);

	m_horisontalSlider = std::make_shared<Slider>(
		GetElementPosition(0.5175f, 1.0f),
		GetElementSize(0.5f, 0.05f),
		Alignment::BOTTOM_MID,
		true,
		m_galaxayScaleFacor,
		resolution
		);
	m_horisontalSlider->SetScrolling(true);

	// btn
	m_zoomInBtn = std::make_shared<ClassicButton>(
		101,
		GetElementPosition(1.0f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"+",
		SoundType::CLICKED_RELEASE_STD
		);
	m_elementsOutUpdates.push_back(m_zoomInBtn);

	m_zoomOutBtn = std::make_shared<ClassicButton>(
		102,
		GetElementPosition(0.95f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"-",
		SoundType::CLICKED_RELEASE_STD
		);
	m_elementsOutUpdates.push_back(m_zoomOutBtn);

	// Galaxy
	auto galaxy = std::make_shared<UIGalaxy>(
		100,
		GetElementPosition(0.52f, 0.45f),
		GetElementSize(0.915f, 0.9f),
		Alignment::MID_MID,
		resolution
		);
	m_elements.push_back(galaxy);
}

GalaxyScene::GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment) {
	GetAlignedCollider(m_pos, m_size, alignment, resolution);

	Initialize(resolution);
}

void GalaxyScene::SetIsScaling(bool isScaling) {
	m_isScaling = isScaling;
}
bool GalaxyScene::GetIsScaling() const {
	return m_isScaling;
}

void GalaxyScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	if (m_isScaling) {
		m_zoomInBtn->CheckAndUpdate(mousePosition, appContext);
		m_zoomOutBtn->CheckAndUpdate(mousePosition, appContext);
	}

	if (m_galaxayScaleFacor > 1.0f) {
		m_horisontalSlider->CheckAndUpdate(mousePosition, appContext);
		m_verticalSlider->CheckAndUpdate(mousePosition, appContext);
	}
}
void GalaxyScene::Render(AppContext const& appContext) {
	Scene::Render(appContext);

	if (m_galaxayScaleFacor > 1.0f) {
		m_horisontalSlider->Render(appContext);
		m_verticalSlider->Render(appContext);
	}

	if (m_isScaling) {
		m_zoomInBtn->Render(appContext);
		m_zoomOutBtn->Render(appContext);
	}
}
void GalaxyScene::Resize(Vector2 resolution, AppContext const& appContext) {
	Scene::Resize(resolution, appContext);

	m_verticalSlider->Resize(resolution, appContext);
	m_horisontalSlider->Resize(resolution, appContext);
	m_zoomInBtn->Resize(resolution, appContext);
	m_zoomOutBtn->Resize(resolution, appContext);
}
