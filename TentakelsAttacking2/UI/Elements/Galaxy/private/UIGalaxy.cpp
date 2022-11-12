//
// Purpur Tentakel
// 12.11.2022
//

#include "UIGalaxy.h"
#include <iostream>

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
}

UIGalaxy::UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution)
	:Focusable(ID), UIElement(pos, size, alignment) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_absoluteSize = m_colider; // just for testing. need to chance to actual galaxy size.
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
}
void UIGalaxy::Resize(Vector2 resolution, AppContext const& appContext) {
	m_colider = {
	m_pos.x * resolution.x,
	m_pos.y * resolution.y,
	m_size.x * resolution.x,
	m_size.y * resolution.y
	};
	// need to scale m_absoluteSize
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

void UIGalaxy::OnEvent(Event const& event) {}
