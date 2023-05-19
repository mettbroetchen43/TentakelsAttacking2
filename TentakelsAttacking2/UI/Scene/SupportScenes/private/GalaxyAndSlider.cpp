//
// Purpur Tentakel
// 09.11.2022
// 

#include "GalaxyAndSlider.h"
#include "AppContext.h"
#include "Slider.h"
#include "Line.h"
#include "UIGalaxy.h"
#include "ClassicButton.h"

void GalaxyScene::Initialize(Vector2 resolution, bool isShowGalaxy) {

	// Galaxy
	m_galaxy = std::make_shared<UIGalaxy>(
		100,
		GetElementPosition(1.0f, 0.0f),
		GetElementSize(0.955f, 0.93f),
		Alignment::TOP_RIGHT,
		resolution,
		isShowGalaxy
		);
	m_galaxy->SetOnZoom([this](float scaleFactor, Vector2 referenceScale) {
		this->Zoom(scaleFactor, referenceScale);
		});
	m_galaxy->SetOnSlide([this](float position, bool isHorzontal) {
		this->Slide(position, isHorzontal);
		});
	m_elements.push_back(m_galaxy);

	// slider
	m_verticalSlider = std::make_shared<Slider>(
		GetElementPosition(0.00f, 0.46f),
		GetElementSize(0.03f, 0.5f),
		Alignment::MID_LEFT,
		resolution,
		false,
		m_galaxy->GetScaleFactor()
		);
	m_verticalSlider->SetOnSlide([this](float position) {
		this->m_galaxy->Slide(position, false);
		});
	m_verticalSlider->SetScrolling(true);

	m_horisontalSlider = std::make_shared<Slider>(
		GetElementPosition(0.5175f, 1.0f),
		GetElementSize(0.5f, 0.05f),
		Alignment::BOTTOM_MID,
		resolution,
		true,
		m_galaxy->GetScaleFactor()
		);
	m_horisontalSlider->SetOnSlide([this](float position) {
		this->m_galaxy->Slide(position, true);
		});
	m_horisontalSlider->SetScrolling(true);

	// btn
	m_zoomInBtn = std::make_shared<ClassicButton>(
		101,
		GetElementPosition(0.091f, 0.95f),
		GetElementSize(0.05f, 0.05f),
		Alignment::TOP_LEFT,
		resolution,
		"+",
		SoundType::CLICKED_RELEASE_STD
		);
	m_zoomInBtn->SetOnPress([this]() {
		this->m_galaxy->Zoom(true);
		});
	m_elementsOutUpdates.push_back(m_zoomInBtn);

	m_zoomOutBtn = std::make_shared<ClassicButton>(
		102,
		GetElementPosition(0.041f, 0.95f),
		GetElementSize(0.05f, 0.05f),
		Alignment::TOP_LEFT,
		resolution,
		"-",
		SoundType::CLICKED_RELEASE_STD
		);
	m_zoomOutBtn->SetOnPress([this]() {
		this->m_galaxy->Zoom(false);
		});
	m_elementsOutUpdates.push_back(m_zoomOutBtn);

	// scale
	m_scaleLineX = std::make_shared<Line>(
		GetElementPosition(0.041f, 0.94f),
		GetElementSize(0.2f, 0.0f),
		Alignment::BOTTOM_LEFT,
		resolution,
		2.0f
		);

	m_scaleLineY = std::make_shared<Line>(
		GetElementPosition(0.036f, 0.93f),
		GetElementSize(0.0f, 0.2f),
		Alignment::BOTTOM_LEFT,
		resolution,
		2.0f
		);

	m_galaxy->Zoom(false, 0);
}

void GalaxyScene::Zoom(float scaleFactor, Vector2 referenceScale) {

	m_verticalSlider->SetAbsoluteDimension(scaleFactor);
	m_horisontalSlider->SetAbsoluteDimension(scaleFactor);

	m_scaleLineX->SetSize(
		Vector2(referenceScale.x / m_resolution.x, 0.0f)
	);

	Vector2 const size{ m_scaleLineY->GetSize() };
	m_scaleLineY->SetSize(
		Vector2(0.0f, referenceScale.y / m_resolution.y)
	);
	m_scaleLineY->SetPosition(
		GetElementPosition(0.036f, 0.93f)
	);
}
void GalaxyScene::Slide(float position, bool isHorizontal) {
	if (isHorizontal) {
		m_horisontalSlider->SetButtonPosition(position);
	}
	else {
		m_verticalSlider->SetButtonPosition(position);
	}
}

GalaxyScene::GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, bool isShowGalaxy)
	: Scene{ pos, size, alignment, resolution } {

	Initialize(resolution, isShowGalaxy);
}

void GalaxyScene::SetIsScaling(bool isScaling) {
	m_galaxy->SetIsScaling(isScaling);
}
bool GalaxyScene::IsScaling() const {
	return m_galaxy->IsScaling();;
}

void GalaxyScene::SetIsEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
	m_galaxy->SetEnabled(isEnabled);
	m_zoomInBtn->SetEnabled(isEnabled);
	m_zoomOutBtn->SetEnabled(isEnabled);
}
bool GalaxyScene::IsEnabled() const {
	return m_isEnabled;
}

Galaxy const* GalaxyScene::GetGalaxy() const {
	return m_galaxy->GetGalaxy();
}

void GalaxyScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (!IsActive()) { return; }

	Scene::CheckAndUpdate(mousePosition, appContext);

	if (IsScaling()) {
		m_zoomInBtn->CheckAndUpdate(mousePosition, appContext);
		m_zoomOutBtn->CheckAndUpdate(mousePosition, appContext);
	}

	if (m_galaxy->GetScaleFactor() > 1.0f) {
		m_horisontalSlider->CheckAndUpdate(mousePosition, appContext);
		m_verticalSlider->CheckAndUpdate(mousePosition, appContext);
	}
}
void GalaxyScene::Render(AppContext const& appContext) {
	if (!IsActive()) { return; }

	Scene::Render(appContext);

	if (m_galaxy->GetScaleFactor() > 1.0f) {
		m_horisontalSlider->Render(appContext);
		m_verticalSlider->Render(appContext);
	}

	if (IsScaling()) {
		m_zoomInBtn->Render(appContext);
		m_zoomOutBtn->Render(appContext);
		m_scaleLineX->Render(appContext);
		m_scaleLineY->Render(appContext);
	}
}
void GalaxyScene::Resize(Vector2 resolution, AppContext const& appContext) {

	Scene::Resize(resolution, appContext);

	m_verticalSlider->Resize(resolution, appContext);
	m_horisontalSlider->Resize(resolution, appContext);
	m_zoomInBtn->Resize(resolution, appContext);
	m_zoomOutBtn->Resize(resolution, appContext);
	m_scaleLineX->Resize(resolution, appContext);
	m_scaleLineY->Resize(resolution, appContext);
}
