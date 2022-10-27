//
// Purpur Tentakel
// 29.08.2022
//

#include "Slider.h"
#include "Allignment.h"
#include "AppContext.h"
#include <iostream>

void Slider::CalculateInitialButton(Vector2 resolution, float absoluteDimension) {
	float sizeX = m_isHorizontal ? m_size.x / absoluteDimension : m_size.x;
	float sizeY = m_isHorizontal ? m_size.y : m_size.y / absoluteDimension;

	m_btn = SliderButton(
		m_pos,
		Vector2(sizeX, sizeY),
		Alignment::TOP_LEFT,
		"",
		SoundType::CLICKED_RELEASE_STD,
		resolution
	);
	m_btn.SetOnPress([this]() {this->Slide();});
}

void Slider::Slide() {
	m_isPressed = true;
	Vector2 mousePosition = GetMousePosition();
	Rectangle btnCollider = m_btn.GetCollider();

	float mousePoint = m_isHorizontal ? mousePosition.x : mousePosition.y;
	float* btnColliderPoint = m_isHorizontal ? &btnCollider.x : &btnCollider.y;
	float btnColliderLength = m_isHorizontal ? btnCollider.width : btnCollider.height;
	float sliderColliderPoint = m_isHorizontal ? m_collider.x : m_collider.y;
	float sliderColliderLength = m_isHorizontal ? m_collider.width : m_collider.height;

	float maxValue = sliderColliderPoint + btnColliderLength / 2;
	float minValue = sliderColliderPoint + sliderColliderLength - btnColliderLength / 2;
	if (mousePoint < maxValue) {
		*btnColliderPoint = sliderColliderPoint;
	}
	else if (mousePoint > minValue) {
		*btnColliderPoint = sliderColliderPoint + sliderColliderLength - btnColliderLength;
	}
	else {
		*btnColliderPoint = mousePoint - btnColliderLength / 2;
	}

	m_btn.SetCollider(btnCollider);
}
void Slider::SlideIfPressed() {
	if (!m_isPressed) { return; }
	if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		m_isPressed = false;
		return;
	}
	Slide();
}
void Slider::MoveButtonIfColiderIsPressed(Vector2 const& mousePosition) {
	bool const hover = CheckCollisionPointRec(mousePosition, m_collider);
	if (!hover) {
		return;
	}

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return;
	}

	Slide();
}

Slider::Slider(Vector2 pos, Vector2 size, Alignment alignment, bool isHorizontal,
	float absoluteDimension, Vector2 resolution)
	: UIElement(pos, size, alignment), m_isHorizontal(isHorizontal) {
	m_texture = AppContext::GetInstance().assetManager.GetTexture(AssetType::GREY);
	m_textureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_texture->width),
		static_cast<float>(m_texture->height)
	};
	m_collider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	CalculateInitialButton(resolution, absoluteDimension);
}

void Slider::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (!m_isPressed) {
		MoveButtonIfColiderIsPressed(mousePosition);
	}
	else {
		SlideIfPressed();
	}
	m_btn.CheckAndUpdate(mousePosition, appContext);
}
void Slider::Render(AppContext const& appContext) {
	DrawTexturePro(*m_texture, m_textureRec, m_collider, Vector2(0.0f, 0.0f), 0, WHITE);
	m_btn.Render(appContext);
}
void Slider::Resize(Vector2 resolution, AppContext const& appContext) {
	m_collider = { m_pos.x * resolution.x, m_pos.y * resolution.y, m_size.x * resolution.x, m_size.y * resolution.y };
	m_btn.Resize(resolution, appContext);
}
