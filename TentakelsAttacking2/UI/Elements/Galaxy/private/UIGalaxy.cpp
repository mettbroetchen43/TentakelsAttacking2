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
#include "Player.h"

void UIGalaxy::Initialize(SendGalaxyPointerEvent const* event) {
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	Galaxy_ty_c_raw galaxy{ event->GetGalaxy() };

	m_currentGalaxy = galaxy;

	for (auto const& p  : galaxy->GetPlanets()) {
		auto planet = std::make_shared<UIPlanet>(
			p->GetID(),
			p->GetID(),
			appContext.playerCollection.GetPlayerByIDOrDefaultPlayer(p->GetPlayer()->GetID()),
			GetAbsolutePosition({
				static_cast<float>(p->GetPos().x),
				static_cast<float>(p->GetPos().y),
				}, appContext),
			m_resolution,
			GetRelativePosition({
				static_cast<float>(p->GetPos().x),
				static_cast<float>(p->GetPos().y),
				}, appContext)
			);
		if (p->IsDestroyed()) {
			planet->SetEnabled(false);
			planet->SetColor(DARKGRAY);
		}
		else if (not p->IsDiscovered() and not event->IsShowGalaxy()) {
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
Vector2 UIGalaxy::GetAbsolutePosition(Vector2 pos, AppContext_ty_c appContext) const {
	Vector2 const newPos{
		(m_collider.x + m_resolution.x * 0.05f) / m_resolution.x,
		(m_collider.y + m_resolution.y * 0.05f) / m_resolution.y,
	};
	Vector2 const newSize{
		(m_collider.width - m_resolution.x * 0.1f) / m_resolution.x,
		(m_collider.height - m_resolution.y * 0.1f) / m_resolution.y,
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
Vector2 UIGalaxy::GetRelativePosition(Vector2 pos, AppContext_ty_c appContext) const {
	Vector2 const newPos{
		m_resolution.x * 0.045f / m_collider.width,
		m_resolution.y * 0.045f / m_collider.height,
	};
	Vector2 const newSize{
		(m_collider.width - m_resolution.x * 0.1f) / m_collider.width,
		(m_collider.height - m_resolution.y * 0.1f) / m_collider.height,
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

bool UIGalaxy::IsPlanetInCollider(UIPlanet_ty planet) const {
	Rectangle const planetCollider{ planet->GetCollider() };

	if (planetCollider.x < m_collider.x) { return false; }
	if (planetCollider.y < m_collider.y) { return false; }
	if (planetCollider.x + planetCollider.width > m_collider.x + m_collider.width) { return false; }
	if (planetCollider.y + planetCollider.height > m_collider.y + m_collider.height) { return false; }

	return true;
}
void UIGalaxy::UpdatePlanetPosition() {
	for (auto const& p : m_uiPlanets) {
		p->UpdatePosition(m_absoluteSize);
	}
}
void UIGalaxy::SelectPlanet(UIPlanet* planet) {
	m_onPlanetClick(planet->GetID());
}

void UIGalaxy::ClampsPositionAndSize() {
	m_absoluteSize.x = m_absoluteSize.x < m_collider.x
		? m_absoluteSize.x
		: m_collider.x;

	m_absoluteSize.x = m_absoluteSize.x + m_absoluteSize.width > m_collider.x + m_collider.width
		? m_absoluteSize.x
		: m_collider.x + m_collider.width - m_absoluteSize.width;

	m_absoluteSize.y = m_absoluteSize.y < m_collider.y 
		? m_absoluteSize.y
		: m_collider.y;

	m_absoluteSize.y = m_absoluteSize.y + m_absoluteSize.height > m_collider.y + m_collider.height
		? m_absoluteSize.y
		: m_collider.y + m_collider.height - m_absoluteSize.height;
}
void UIGalaxy::PrepForOnSlide() {
	float deferens{ m_absoluteSize.width - m_collider.width };
	float offset{ m_collider.x - m_absoluteSize.x };
	float percent{ offset / deferens * 100 };
	m_onSlide(percent, true);

	deferens = m_absoluteSize.height - m_collider.height;
	offset = m_collider.y - m_absoluteSize.y;
	percent = offset / deferens * 100;
	m_onSlide(percent, false);
}
void UIGalaxy::MoveByKey(Direction direction, float speed) {
	float deferens;
	float offset;
	float percent;

	switch (direction) {
		case Direction::UP:
			deferens = m_absoluteSize.height - m_collider.height;
			offset = m_collider.y - m_absoluteSize.y;
			percent = offset / deferens * 100 + speed;
			Slide(percent, false);
			break;
		case Direction::DOWN:
			deferens = m_absoluteSize.height - m_collider.height;
			offset = m_collider.y - m_absoluteSize.y;
			percent = offset / deferens * 100 - speed;
			Slide(percent, false);
			break;
		case Direction::LEFT:
			deferens = m_absoluteSize.width - m_collider.width;
			offset = m_collider.x - m_absoluteSize.x;
			percent = offset / deferens * 100 + speed;
			Slide(percent, true);
			break;
		case Direction::RIGHT:
			deferens = m_absoluteSize.width - m_collider.width;
			offset = m_collider.x - m_absoluteSize.x;
			percent = offset / deferens * 100 - speed;
			Slide(percent, true);
			break;
	}
	ClampsPositionAndSize();
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

	ClampsPositionAndSize();
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
	:Focusable{ ID }, UIElement{ pos, size, alignment, resolution },
	m_isShowGalaxy(isShowGalaxy) {
	m_absoluteSize = m_collider;

	AppContext_ty appContext{ AppContext::GetInstance() };

	appContext.eventManager.AddListener(this);

	if (isShowGalaxy) {
		GetShowGalaxyPointerEvent event;
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		GetGalaxyPointerEvent event;
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

	Rectangle newSize{
		m_absoluteSize.x,
		m_absoluteSize.y,
		m_collider.width * m_scaleFactor,
		m_collider.height * m_scaleFactor,
	};

	Vector2 const deferens{
		newSize.width - m_absoluteSize.width,
		newSize.height - m_absoluteSize.height,
	};

	Vector2 mouseFactor{ 0.5f,0.5f };
	Vector2 const mousePosition{ GetMousePosition() };
	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		mouseFactor.x = (mousePosition.x - m_collider.x) / m_collider.width;
		mouseFactor.y = (mousePosition.y - m_collider.y) / m_collider.height;
	}

	newSize.x -= deferens.x * mouseFactor.x;
	newSize.y -= deferens.y * mouseFactor.y;

	m_absoluteSize = newSize;

	ClampsPositionAndSize();

	m_onZoom(m_scaleFactor, GetCurrentScaleReference());
	PrepForOnSlide();
	UpdatePlanetPosition();
}
void UIGalaxy::Slide(float position, bool isHorizontal) {
	if (isHorizontal) {
		float const deferens{ m_absoluteSize.width - m_collider.width };
		float const offset{ deferens / 100 * position };
		m_absoluteSize.x = m_collider.x - offset;
	}
	else {
		float const deferens{ m_absoluteSize.height - m_collider.height };
		float const offset{ deferens / 100 * position };
		m_absoluteSize.y = m_collider.y - offset;
	}
	ClampsPositionAndSize();
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

void UIGalaxy::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (m_isScaling) {
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
			float const mouseWheel{ GetMouseWheelMove() };
			if (mouseWheel != 0.0f) {
				Zoom(mouseWheel > 0.0f, 5);
			}
		}

		if (IsKeyDown(KEY_UP)) { MoveByKey(Direction::UP, 2.0f); }
		if (IsKeyDown(KEY_DOWN)) { MoveByKey(Direction::DOWN, 2.0f); }
		if (IsKeyDown(KEY_LEFT)) { MoveByKey(Direction::LEFT, 1.5f); }
		if (IsKeyDown(KEY_RIGHT)) { MoveByKey(Direction::RIGHT, 1.5f); }

		if (CheckCollisionPointRec(mousePosition, m_collider)) {
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
		for (auto const& p : m_uiPlanets) {

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
				for (auto const& p : m_uiPlanets) {
					AddFocusElement(p.get());
				}
			}
		}

		if (IsNestedFocus()) {
			if (IsBackInputPressed()
				or !CheckCollisionPointRec(mousePosition, m_collider)) {
				DeleteFocusLayer();
				m_isNestedFocus = false;
			}
		}
	}
}
void UIGalaxy::Render(AppContext_ty_c appContext) {
	for (auto const& p : m_uiPlanets) {
		if (IsPlanetInCollider(p)) {
			p->Render(appContext);
		}
	}
}
void UIGalaxy::Resize(Vector2 resolution, AppContext_ty_c appContext) {

	m_absoluteSize = {
		m_absoluteSize.x / m_resolution.x * resolution.x,
		m_absoluteSize.y / m_resolution.y * resolution.y,
		m_absoluteSize.width / m_resolution.x * resolution.x,
		m_absoluteSize.height / m_resolution.y * resolution.y,
	};

	UIElement::Resize(resolution, appContext);

	for (auto const& p : m_uiPlanets) {
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
	return UIElement::GetCollider();
}

Galaxy_ty_raw UIGalaxy::GetGalaxy() const {
	return m_currentGalaxy;
}

void UIGalaxy::OnEvent(Event const& event) {
	
	if (auto const* galaxyEvent = dynamic_cast<SendGalaxyPointerEvent const*>(&event)) {
		Initialize(galaxyEvent);
		return;
	}
}
