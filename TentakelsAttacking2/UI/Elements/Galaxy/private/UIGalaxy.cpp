//
// Purpur Tentakel
// 12.11.2022
//

#include "UIGalaxy.h"
#include "GenerelEvents.hpp"
#include "AppContext.h"
#include "Galaxy.h"
#include "UIPlanet.h"
#include "HInput.h"
#include "HFocusEvents.h"

void UIGalaxy::Initialize(Galaxy const* const galaxy) {
	AppContext& appContext = AppContext::GetInstance();

	m_currentGalaxy = galaxy;

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
		planet->SetOnClick([this](UIPlanet* planet) {
			this->SelectPlanet(planet);
			});
		planet->UpdatePosition(m_absoluteSize);
		m_uiPlanets.push_back(planet);
	}
	m_onZoom(1.0f, GetCurrentScaleReference());
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
	if (m_isShowGalaxy) {
		return {
			newPos.x + pos.x / appContext.constants.world.showDimensionX * newSize.x,
			newPos.y + pos.y / appContext.constants.world.showDimensionY * newSize.y,
		};
	}
	else {
		return {
			newPos.x + pos.x / appContext.constants.world.currentDimensionX * newSize.x,
			newPos.y + pos.y / appContext.constants.world.currentDimensionY * newSize.y,
		};
	}

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
	if (m_isShowGalaxy) {
		return {
			newPos.x + pos.x / appContext.constants.world.showDimensionX * newSize.x,
			newPos.x + pos.y / appContext.constants.world.showDimensionY * newSize.y,
		};
	}
	else {
		return {
			newPos.x + pos.x / appContext.constants.world.currentDimensionX * newSize.x,
			newPos.x + pos.y / appContext.constants.world.currentDimensionY * newSize.y,
		};
	}

}

bool UIGalaxy::IsPlanetInCollider(std::shared_ptr<UIPlanet> planet) const {
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
void UIGalaxy::SelectPlanet(UIPlanet* planet) {
	m_onPlanetClick(planet->GetID());
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

Vector2 UIGalaxy::GetCurrentScaleReference() const {
	return {
		m_absoluteSize.width / m_currentGalaxy->GetSize().x * 10,
		m_absoluteSize.height / m_currentGalaxy->GetSize().y * 10
	};
}

UIGalaxy::UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment,
	Vector2 resolution, bool isShowGalaxy)
	:Focusable(ID), UIElement(pos, size, alignment), m_resolution(resolution),
	m_isShowGalaxy(isShowGalaxy) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_absoluteSize = m_colider;

	AppContext& appContext = AppContext::GetInstance();

	appContext.eventManager.AddListener(this);

	if (isShowGalaxy) {
		auto event = GetShowGalaxyPointerEvent();
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		auto event = GetGalaxyPointerEvent();
		appContext.eventManager.InvokeEvent(event);
	}

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
	return m_scaleFactor;
}

void UIGalaxy::Zoom(bool zoomIn, int factor) {
	if (!m_isScaling) { return; }

	if (zoomIn) { m_scaleFactor *= 1.0f + 0.01f * factor; }
	else { m_scaleFactor *= 1.0f - 0.01f * factor; }

	if (m_scaleFactor < 1.0f) { m_scaleFactor = 1.0f; }
	if (m_scaleFactor > 7.5f) { m_scaleFactor = 7.5f; }

	Rectangle newSize = {
		m_absoluteSize.x,
		m_absoluteSize.y,
		m_colider.width * m_scaleFactor,
		m_colider.height * m_scaleFactor,
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

	m_onZoom(m_scaleFactor, GetCurrentScaleReference());
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

void UIGalaxy::SetOnZoom(std::function<void(float, Vector2)> onZoom) {
	m_onZoom = onZoom;
}
void UIGalaxy::SetOnSlide(std::function<void(float, bool)> onSlide) {
	m_onSlide = onSlide;
}
void UIGalaxy::SetOnPlanetClick(std::function<void(unsigned int)> onPlanetClick) {
	m_onPlanetClick = onPlanetClick;
}

void UIGalaxy::UpdateColider(Vector2 resolution) {
	m_colider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
	m_absoluteSize = {
	m_absoluteSize.x / m_resolution.x * resolution.x,
	m_absoluteSize.y / m_resolution.y * resolution.y,
	m_absoluteSize.width / m_resolution.x * resolution.x,
	m_absoluteSize.height / m_resolution.y * resolution.y,
	};

	m_resolution = resolution;
}

void UIGalaxy::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (m_isScaling) {
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
			float mouseWheel = GetMouseWheelMove();
			if (mouseWheel != 0.0f) {
				Zoom(mouseWheel > 0.0f, 5);
			}
		}

		if (IsKeyDown(KEY_UP)) { MoveByKey(Direction::UP, 2.0f); }
		if (IsKeyDown(KEY_DOWN)) { MoveByKey(Direction::DOWN, 2.0f); }
		if (IsKeyDown(KEY_LEFT)) { MoveByKey(Direction::LEFT, 1.5f); }
		if (IsKeyDown(KEY_RIGHT)) { MoveByKey(Direction::RIGHT, 1.5f); }

		if (CheckCollisionPointRec(mousePosition, m_colider)) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				m_isScrollingByMouse = true;
			}
		}
		if (m_isScrollingByMouse) {
			MoveByMouse(mousePosition);
		}
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			m_lastMousePosition = { 0.0f, 0.0f };
			m_isScrollingByMouse = false;
		}
	}

	if (m_isEnabled) {
		for (auto& p : m_uiPlanets) {

			if (IsPlanetInCollider(p) != p->IsEnabled()) {
				p->SetEnabled(IsPlanetInCollider(p));
				if (!IsPlanetInCollider(p) && p->IsFocused()) {
					SelectNextFocusElement();
				}
			}

			if (IsPlanetInCollider(p)) {
				p->CheckAndUpdate(mousePosition, appContext);
			}
		}

		if (IsFocused() && !IsNestedFocus()) {
			if (IsConfirmInputPressed()) {
				m_isNestedFocus = true;
				AddFocusLayer();
				for (auto& p : m_uiPlanets) {
					AddFocusElement(p.get());
				}
			}
		}

		if (IsNestedFocus()) {
			if (IsBackInputPressed()
				|| !CheckCollisionPointRec(mousePosition, m_colider)) {
				DeleteFocusLayer();
				m_isNestedFocus = false;
			}
		}
	}
}
void UIGalaxy::Render(AppContext const& appContext) {
	/*DrawRectangleLinesEx(
		m_colider,
		2.0f,
		WHITE
	);*/
	/*DrawRectangleLinesEx(
		m_absoluteSize,
		3.0f,
		PURPLE
	);*/

	for (auto& p : m_uiPlanets) {
		if (IsPlanetInCollider(p)) {
			p->Render(appContext);
		}
	}
}
void UIGalaxy::Resize(Vector2 resolution, AppContext const& appContext) {

	m_colider = {
	m_pos.x * resolution.x,
	m_pos.y * resolution.y,
	m_size.x * resolution.x,
	m_size.y * resolution.y
	};
	m_absoluteSize = {
		m_absoluteSize.x / m_resolution.x * resolution.x,
		m_absoluteSize.y / m_resolution.y * resolution.y,
		m_absoluteSize.width / m_resolution.x * resolution.x,
		m_absoluteSize.height / m_resolution.y * resolution.y,
	};

	m_resolution = resolution;

	for (auto& p : m_uiPlanets) {
		p->Resize(resolution, appContext);
		p->UpdatePosition(m_absoluteSize);
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
	
	if (auto const* GalaxyEvent = dynamic_cast<SendGalaxyPointerEvent const*>(&event)) {
		Initialize(GalaxyEvent->GetGalaxy());
		return;
	}
}
