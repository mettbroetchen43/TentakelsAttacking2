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
}

void UIGalaxy::SetOnZoom(std::function<void(float)> onZoom) {
	m_onZoom = onZoom;
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
