//
// Purpur Tentakel
// 27.10.2022
//

#include "SliderAndInputLine.h"
#include "ClassicButton.h"
#include "Slider.h"
#include "HRandom.h"
#include <iostream>

void SliderAndInputLine::Initialize(unsigned int focusID, Vector2 resolution) {
	m_inputLine = std::make_shared<InputLine<int>>(
		focusID,
		GetElementPosition(0.77f, 0.0f),
		GetElementSize(0.13f, 1.0f),
		Alignment::TOP_LEFT,
		5,
		resolution
		);
	m_inputLine->SetOnEnter([this]() {
		this->BtnPressed();
		});
	m_inputLine->SetValue(m_currentValue);
	ValidateCurrentValue();
	m_slided = true;
	m_inputLine->SetPlaceholderText("%");
	m_elements.push_back(m_inputLine);

	++focusID;

	m_btn = std::make_shared<ClassicButton>(
		focusID,
		GetElementPosition(0.9f, 0.0f),
		GetElementSize(0.1f, 1.0f),
		Alignment::TOP_LEFT,
		resolution,
		"Set",
		SoundType::CLICKED_RELEASE_STD
		);
	m_btn->SetOnClick([this]() {
		this->BtnPressed();
	});
	m_btn->SetEnabled(false);
	m_elements.push_back(m_btn);

	m_slider = std::make_shared<Slider>(
		GetElementPosition(0.0f, 0.1f),
		GetElementSize(0.75f, 0.8f),
		Alignment::TOP_LEFT,
		true,
		10.0f,
		resolution
		);
	m_slider->SetOnSlide([this](float position) {
		Slide(position);
		});
	SetSliderValue();
	m_elements.push_back(m_slider);
}

void SliderAndInputLine::BtnPressed() {
	SaveValue();
	m_slided = false;
	SetSliderValue();
	m_btn->SetEnabled(false);
}
void SliderAndInputLine::SaveValue() {
	ValidateCurrentValue();
	m_onSave(m_currentValue);
}
void SliderAndInputLine::Slide(float position) {
	m_currentValue = static_cast<int>(((m_maxValue - m_minValue) * position / 100) + m_minValue);
	m_inputLine->SetValue(m_currentValue);
	SaveValue();
	m_slided = true;
}
void SliderAndInputLine::ValidateCurrentValue() {
	m_currentValue = m_inputLine->GetValue();

	if (m_currentValue < m_minValue) {
		m_currentValue = m_minValue;
	} 
	else if (m_currentValue > m_maxValue) {
		m_currentValue = m_maxValue;
	}

	m_inputLine->SetValue(m_currentValue);
}
void SliderAndInputLine::SetSliderValue() const {
	float percent = static_cast<float>(m_currentValue - m_minValue) / (m_maxValue - m_minValue) * 100;
	m_slider->SetButtonPosition(percent);
}

SliderAndInputLine::SliderAndInputLine(unsigned int focusID, Vector2 pos,
	Vector2 size, Alignment alignment,
	int minValue, int maxValue, int initialValue,
	Vector2 resolution)
	: Scene(pos, size, alignment), m_minValue(minValue), m_maxValue(maxValue) {
	GetAlignedCollider(m_pos, m_size, alignment, resolution);
	m_currentValue = initialValue;
	Initialize(focusID, resolution);

}

void SliderAndInputLine::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
	

	if (m_inputLine->HasValueChanced()) {
		if (!m_slided) {
			m_btn->SetEnabled(true);
		} else {
			m_slided = false;
		}
	}
}

void SliderAndInputLine::SetOnSave(std::function<void(int)> onSave) {
	m_onSave = onSave;
}
void SliderAndInputLine::SetValue(int value) {
	m_currentValue = value;
	ValidateCurrentValue();
	m_inputLine->SetValue(m_currentValue);
	m_slider->SetButtonPosition(static_cast<float>(m_currentValue));
	m_slided = true;
}

void SliderAndInputLine::RandomValue() {
	Random& random = Random::GetInstance();
	m_currentValue = static_cast<int>(random.random(m_maxValue - m_minValue) + m_minValue);
	m_inputLine->SetValue(m_currentValue);
	SetSliderValue();
}
