//
// Purpur Tentakel
// 29.08.2022
//

#include "Slider.h"
#include "Allignment.h"
#include "AppContext.h"

void Slider::CalculateInitialButton() {
	float sizeX = m_isHorizontal ? m_size.x / m_absoluteDimension : m_size.x;
	float sizeY = m_isHorizontal ? m_size.y : m_size.y / m_absoluteDimension;

	m_btn = SliderButton(
		m_pos,
		Vector2(sizeX, sizeY),
		Alignment::TOP_LEFT,
		m_resolution,
		"",
		SoundType::CLICKED_RELEASE_STD
	);
	m_btn.SetOnPress([this]() {this->Slide();});
}

void Slider::CalculateOnSlide() const {

	auto btnColider = m_btn.GetColider();

	float total = m_isHorizontal
		? m_colider.width - btnColider.width
		: m_colider.height - btnColider.height;
	float slided = m_isHorizontal
		? btnColider.x - m_colider.x
		: btnColider.y - m_colider.y;

	float calculated = slided / total * 100;

	m_onSlide(calculated);
}
void Slider::Slide() {
	m_isPressed = true;
	Vector2 mousePosition = GetMousePosition();
	if (m_isHorizontal) {
		mousePosition.x -= m_btnOffset;
	}
	else {
		mousePosition.y -= m_btnOffset;
	}
	Rectangle btnCollider = m_btn.GetColider();

	float mousePoint = m_isHorizontal ? mousePosition.x : mousePosition.y;
	float* btnColliderPoint = m_isHorizontal ? &btnCollider.x : &btnCollider.y;
	float btnColliderLength = m_isHorizontal ? btnCollider.width : btnCollider.height;
	float sliderColliderPoint = m_isHorizontal ? m_colider.x : m_colider.y;
	float sliderColliderLength = m_isHorizontal ? m_colider.width : m_colider.height;

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

	CalculateOnSlide();
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
	bool const hover = CheckCollisionPointRec(mousePosition, m_colider);
	if (!hover) {
		return;
	}

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return;
	}

	Slide();
}

void Slider::SlideIfScroll() {
	if (!m_isScroll) { return; }
	if (m_isPressed) { return; }
	if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) { return; }

	float mouseWheel = GetMouseWheelMove() * -1;
	if (mouseWheel == 0.0f) { return; }
	if (m_isHorizontal != (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) { return; }

	auto btnColider = m_btn.GetColider();
	float total = m_isHorizontal
		? m_colider.width - btnColider.width
		: m_colider.height - btnColider.height;

	float slidingDiference = total / 100 * mouseWheel * 3;

	if (m_isHorizontal) {
		float value =  btnColider.x + slidingDiference;
		value = value < m_colider.x ? m_colider.x : value;
		value = value > m_colider.x + total ? m_colider.x + total : value;
		btnColider.x = value;
	}
	else {
		float value = btnColider.y + slidingDiference;
		value = value < m_colider.y ? m_colider.y : value;
		value = value > m_colider.y + total ? m_colider.y + total : value;
		btnColider.y = value;
	}

	m_btn.SetCollider(btnColider);
	CalculateOnSlide();
}

void Slider::SetOffset(Vector2 mousePosition) {

	auto btnColider = m_btn.GetColider();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		&& !CheckCollisionPointRec(mousePosition, btnColider)) {
		m_btnOffset = 0.0f;
			return;
	}

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		|| !CheckCollisionPointRec(mousePosition, btnColider)) { return; }

	if (m_isHorizontal) {
		m_btnOffset = mousePosition.x - (btnColider.x + (btnColider.width / 2));
	}
	else {
		m_btnOffset = mousePosition.y - (btnColider.y + (btnColider.height / 2));
	}
}

Slider::Slider(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, 
	bool isHorizontal, float absoluteDimension)
	: UIElement(pos, size, alignment, resolution), m_isHorizontal(isHorizontal),
	m_absoluteDimension(absoluteDimension) {
	m_texture = AppContext::GetInstance().assetManager.GetTexture(AssetType::GREY);
	m_textureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_texture->width),
		static_cast<float>(m_texture->height)
	};
	CalculateInitialButton();
}

void Slider::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	if (!m_isEnabled) { return; }

	SetOffset(mousePosition);

	if (!m_isPressed) {
		MoveButtonIfColiderIsPressed(mousePosition);
	}
	else {
		SlideIfPressed();
	}

	SlideIfScroll();

	m_btn.CheckAndUpdate(mousePosition, appContext);
}
void Slider::Render(AppContext const& appContext) {
	DrawTexturePro(
		*m_texture,
		m_textureRec,
		m_colider,
		Vector2(0.0f, 0.0f),
		0,
		WHITE
	);
	m_btn.Render(appContext);
}
void Slider::Resize(Vector2 resolution, AppContext const& appContext) {

	UIElement::Resize(resolution, appContext);

	m_btn.Resize(resolution, appContext);
}

void Slider::SetOnSlide(std::function<void(float)> onSlide) {
	m_onSlide = onSlide;
}
void Slider::SetButtonPosition(float position) {
	auto btnColider = m_btn.GetColider();

	float total = m_isHorizontal
		? m_colider.width - btnColider.width
		: m_colider.height - btnColider.height;

	float differenz = total / 100 * position;
	float newPosition = m_isHorizontal
		? m_colider.x + differenz
		: m_colider.y + differenz;

	if (m_isHorizontal) {
		btnColider.x = newPosition;
	}
	else {
		btnColider.y = newPosition;
	}

	m_btn.SetCollider(btnColider);
}

void Slider::SetScrolling(bool isScroll) {
	m_isScroll = isScroll;
}
bool Slider::IsScrolling() const {
	return m_isScroll;
}

void Slider::SetAboluteDimension(float absolutDimension) {
	m_absoluteDimension = absolutDimension;
	CalculateInitialButton();
}
float Slider::GetAbsoluteDimension() const {
	return m_absoluteDimension;
}

void Slider::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
	m_btn.SetEnabled(isEnabled);
}
