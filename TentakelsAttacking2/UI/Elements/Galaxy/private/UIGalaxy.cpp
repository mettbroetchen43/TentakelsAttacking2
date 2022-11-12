//
// Purpur Tentakel
// 12.11.2022
//

#include "UIGalaxy.h"
#include "GenerelEvents.hpp"
#include "AppContext.h"
#include "Galaxy.h"
#include "UIPlanet.h"
#include <iostream>

void UIGalaxy::Initialize(Galaxy const* const galaxy) {
	AppContext& appContext = AppContext::GetInstance();

	for (auto& p  : galaxy->GetPlanets()) {
		auto planet = std::make_shared<UIPlanet>(
			p->GetID(),
			p->GetID(),
			GetAbsolutePosition({
				static_cast<float>(p->GetPos().x),
				static_cast<float>(p->GetPos().y),
				}, appContext),
			appContext.playerCollection.GetColorByID(p->GetID()),
			GetRelativePosition({
				static_cast<float>(p->GetPos().x),
				static_cast<float>(p->GetPos().y),
				}, appContext),
			m_resolution
			);
		if (p->IsDestroyed()) {
			planet->SetEnabled(false);
			planet->SetColor(GRAY);
		}
		m_uiPlanets.push_back(planet);
	}
}
Vector2 UIGalaxy::GetAbsolutePosition(Vector2 pos, AppContext const& appContext) const {
	Vector2 newPos = {
		(m_colider.x + m_resolution.x * 0.05f) / m_resolution.x,
		(m_colider.y + m_resolution.y * 0.05f) / m_resolution.y,
	};
	Vector2 newSize = {
		(m_colider.width - m_resolution.x * 0.1f) / m_resolution.x,
		(m_colider.height - m_resolution.y * 0.1f) / m_resolution.y,
	};
	return {
		newPos.x + pos.x / appContext.constants.world.currentDimensionX * newSize.x,
		newPos.y + pos.y / appContext.constants.world.currentDimensionY * newSize.y,
	};
}
Vector2 UIGalaxy::GetRelativePosition(Vector2 pos, AppContext const& appContext) const {
	Vector2 newPos = {
		m_resolution.x * 0.045f / m_colider.width,
		m_resolution.y * 0.045f / m_colider.height,
	};
	Vector2 newSize = {
		(m_colider.width - m_resolution.x * 0.1f) / m_colider.width,
		(m_colider.height - m_resolution.y * 0.1f) / m_colider.height,
	};
	return {
		newPos.x + pos.x / appContext.constants.world.currentDimensionX * newSize.x,
		newPos.x + pos.y / appContext.constants.world.currentDimensionY * newSize.y,
	};
}

bool UIGalaxy::IsPlanetInColider(std::shared_ptr<UIPlanet> planet) const {
	Rectangle planetColider = planet->GetCollider();

	if (planetColider.x < m_colider.x) { return false; }
	if (planetColider.y < m_colider.y) { return false; }
	if (planetColider.x + planetColider.width > m_colider.x + m_colider.width) { return false; }
	if (planetColider.y + planetColider.height > m_colider.y + m_colider.height) { return false; }

	return true;
}
void UIGalaxy::UpdatePlanetPosition() {
	for (auto& p : m_uiPlanets) {
		p->UpdatePosition(m_absoluteSize);
	}
}

void UIGalaxy::CheckPosition() {
	m_absoluteSize.x = m_absoluteSize.x < m_colider.x
		? m_absoluteSize.x
		: m_colider.x;

	m_absoluteSize.x = m_absoluteSize.x + m_absoluteSize.width > m_colider.x + m_colider.width
		? m_absoluteSize.x
		: m_colider.x + m_colider.width - m_absoluteSize.width;

	m_absoluteSize.y = m_absoluteSize.y < m_colider.y 
		? m_absoluteSize.y
		: m_colider.y;

	m_absoluteSize.y = m_absoluteSize.y + m_absoluteSize.height > m_colider.y + m_colider.height
		? m_absoluteSize.y
		: m_colider.y + m_colider.height - m_absoluteSize.height;
}
void UIGalaxy::PrepForOnSlide() {
	float differenz = m_absoluteSize.width - m_colider.width;
	float offset = m_colider.x - m_absoluteSize.x;
	float percent = offset / differenz * 100;
	m_onSlide(percent, true);

	differenz = m_absoluteSize.height - m_colider.height;
	offset = m_colider.y - m_absoluteSize.y;
	percent = offset / differenz * 100;
	m_onSlide(percent, false);
}
void UIGalaxy::MoveByKey(Direction direction, float speed) {
	float differenz;
	float offset;
	float percent;

	switch (direction) {
		case Direction::UP:
			differenz = m_absoluteSize.height - m_colider.height;
			offset = m_colider.y - m_absoluteSize.y;
			percent = offset / differenz * 100 + speed;
			Slide(percent, false);
			break;
		case Direction::DOWN:
			differenz = m_absoluteSize.height - m_colider.height;
			offset = m_colider.y - m_absoluteSize.y;
			percent = offset / differenz * 100 - speed;
			Slide(percent, false);
			break;
		case Direction::LEFT:
			differenz = m_absoluteSize.width - m_colider.width;
			offset = m_colider.x - m_absoluteSize.x;
			percent = offset / differenz * 100 + speed;
			Slide(percent, true);
			break;
		case Direction::RIGHT:
			differenz = m_absoluteSize.width - m_colider.width;
			offset = m_colider.x - m_absoluteSize.x;
			percent = offset / differenz * 100 - speed;
			Slide(percent, true);
			break;
	}
	CheckPosition();
	UpdatePlanetPosition();
}
void UIGalaxy::MoveByMouse(Vector2 mousePosition) {
	if (m_lastMousePosition.x == 0.0f
		&& m_lastMousePosition.y == 0.0f) {
		m_lastMousePosition = mousePosition;
		return;
	}

	m_absoluteSize.x -= m_lastMousePosition.x - mousePosition.x;
	m_absoluteSize.y -= m_lastMousePosition.y - mousePosition.y;

	m_lastMousePosition = mousePosition;

	CheckPosition();
	PrepForOnSlide();
	UpdatePlanetPosition();
}

UIGalaxy::UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution)
	:Focusable(ID), UIElement(pos, size, alignment), m_resolution(resolution) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_absoluteSize = m_colider; // just for testing. need to chance to actual galaxy size.

	AppContext& appContext = AppContext::GetInstance();

	appContext.eventManager.AddListener(this);

	auto event = GetGalaxyCopyEvent();
	appContext.eventManager.InvokeEvent(event);
}
UIGalaxy::~UIGalaxy() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void UIGalaxy::SetIsScaling(bool isScaling) {
	m_isScaling = isScaling;
}
bool UIGalaxy::IsScaling() const {
	return m_isScaling;
}

float UIGalaxy::GetScaleFactor() const {
	return m_scaleFacor;
}

void UIGalaxy::Zoom(bool zoomIn, int factor) {
	if (!m_isScaling) { return; }

	if (zoomIn) { m_scaleFacor += 0.01f * factor; }
	else { m_scaleFacor -= 0.01f * factor; }

	if (m_scaleFacor < 1.0f) { m_scaleFacor = 1.0f; }

	Rectangle newSize = {
		m_absoluteSize.x,
		m_absoluteSize.y,
		m_colider.width * m_scaleFacor,
		m_colider.height * m_scaleFacor,
	};

	Vector2 differenz = {
		newSize.width - m_absoluteSize.width,
		newSize.height - m_absoluteSize.height,
	};

	Vector2 mouseFacor = { 0.5f,0.5f };
	Vector2 mousePosition = GetMousePosition();
	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		mouseFacor.x = (mousePosition.x - m_colider.x) / m_colider.width;
		mouseFacor.y = (mousePosition.y - m_colider.y) / m_colider.height;
	}

	newSize.x -= differenz.x * mouseFacor.x;
	newSize.y -= differenz.y * mouseFacor.y;

	m_absoluteSize = newSize;

	CheckPosition();

	m_onZoom(m_scaleFacor);
	PrepForOnSlide();
	UpdatePlanetPosition();
}
void UIGalaxy::Slide(float position, bool isHorizontal) {
	if (isHorizontal) {
		float differenz = m_absoluteSize.width - m_colider.width;
		float offset = differenz / 100 * position;
		m_absoluteSize.x = m_colider.x - offset;
	}
	else {
		float differenz = m_absoluteSize.height - m_colider.height;
		float offset = differenz / 100 * position;
		m_absoluteSize.y = m_colider.y - offset;
	}
	CheckPosition();
	PrepForOnSlide();
	UpdatePlanetPosition();
}

void UIGalaxy::SetOnZoom(std::function<void(float)> onZoom) {
	m_onZoom = onZoom;
}
void UIGalaxy::SetOnSlide(std::function<void(float, bool)> onSlide) {
	m_onSlide = onSlide;
}

void UIGalaxy::UpdateColider(Vector2 resolution) {
	m_colider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
	// need to scale m_absoluteSize
}

void UIGalaxy::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (m_isScaling) {
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
			float mouseWheel = GetMouseWheelMove();
			if (mouseWheel != 0.0f) {
				Zoom(mouseWheel > 0.0f, 3);
			}
		}

		if (IsKeyDown(KEY_UP)) { MoveByKey(Direction::UP,2.0f); }
		if (IsKeyDown(KEY_DOWN)) { MoveByKey(Direction::DOWN, 2.0f); }
		if (IsKeyDown(KEY_LEFT)) { MoveByKey(Direction::LEFT, 2.0f); }
		if (IsKeyDown(KEY_RIGHT)) { MoveByKey(Direction::RIGHT, 2.0f); }

		if (CheckCollisionPointRec(mousePosition, m_colider)) {
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
				MoveByMouse(mousePosition);
			}
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			m_lastMousePosition = { 0.0f, 0.0f };
		}
	}

	for (auto& p : m_uiPlanets) {
		p->CheckAndUpdate(mousePosition, appContext);
	}

}
void UIGalaxy::Render(AppContext const& appContext) {
	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);
	DrawRectangleLinesEx(
		m_absoluteSize,
		3.0f,
		PURPLE
	);

	for (auto& p : m_uiPlanets) {
		if (IsPlanetInColider(p)) {
			p->Render(appContext);
		}
	}
}
void UIGalaxy::Resize(Vector2 resolution, AppContext const& appContext) {
	m_resolution = resolution;

	m_colider = {
	m_pos.x * resolution.x,
	m_pos.y * resolution.y,
	m_size.x * resolution.x,
	m_size.y * resolution.y
	};
	// need to scale m_absoluteSize

	for (auto& p : m_uiPlanets) {
		p->Resize(resolution, appContext);
	}
}


void UIGalaxy::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
}
bool UIGalaxy::IsEnabled() const {
	return m_isEnabled;
}
Rectangle UIGalaxy::GetCollider() const {
	return m_colider;
}

void UIGalaxy::OnEvent(Event const& event) {
	
	if (auto const* GalaxyEvent = dynamic_cast<SendGalaxyCopyEvent const*>(&event)) {
		Initialize(GalaxyEvent->GetGalaxy());
		return;
	}
}
