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
		100,
		GetElementPosition(1.0f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"+",
		SoundType::CLICKED_RELEASE_STD
		);
	m_zoomInBtn->SetOnPress([this]() {
		this->SetScale(true);
		});

	m_zoomOutBtn = std::make_shared<ClassicButton>(
		101,
		GetElementPosition(0.95f, 1.0f),
		GetElementSize(0.05f, 0.05f),
		Alignment::BOTTOM_RIGHT,
		resolution,
		"-",
		SoundType::CLICKED_RELEASE_STD
		);
	m_zoomOutBtn->SetOnPress([this]() {
		this->SetScale(false);
		});

	// Galaxy
	auto event = GetGalaxyCopy();
	appContext.eventManager.InvokeEvent(event);
}

void GalaxyScene::SetScale(bool scaleIn) {
	if (scaleIn) { m_galaxayScaleFacor += 0.01f; }
	else { m_galaxayScaleFacor -= 0.01f; }

	if (m_galaxayScaleFacor < 1.0f) { m_galaxayScaleFacor = 1.0f; }

	m_horisontalSlider->SetAboluteDimension(m_galaxayScaleFacor);
	m_verticalSlider->SetAboluteDimension(m_galaxayScaleFacor);
}

GalaxyScene::GalaxyScene(Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment) {
	GetAlignedCollider(m_pos, m_size, alignment, resolution);

	AppContext::GetInstance().eventManager.AddListener(this);

	Initialize(resolution);
}
GalaxyScene::~GalaxyScene() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void GalaxyScene::SetIsScaling(bool isScaling) {
	m_isScaling = isScaling;
}
bool GalaxyScene::GetIsScaling() const {
	return m_isScaling;
}

void GalaxyScene::OnEvent(Event const& event) {

	if (auto const* GalaxyEvent = dynamic_cast<SendGalaxyCopy const*>(&event)) {
		/*m_currentGalaxy = GalaxyEvent->GetGalaxy();
		InitialGalaxy();*/
		return;
	}
}

void GalaxyScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	if (m_isScaling) {
		m_zoomInBtn->CheckAndUpdate(mousePosition, appContext);
		m_zoomOutBtn->CheckAndUpdate(mousePosition, appContext);

		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
			float mouse = GetMouseWheelMove();
			if (mouse != 0.0f) {
				SetScale(mouse > 0);
				SetScale(mouse > 0);
			}
		}
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
