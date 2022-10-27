//
// Purpur Tentakel
// 27.10.2022
//

#include "SliderAndInputLine.h"
#include "ClassicButton.h"
#include "Slider.h"
#include <iostream>

void SliderAndInputLine::Initialize(unsigned int focusID, Vector2 resolution) {
	m_slider = std::make_shared<Slider>(
		GetElementPosition(0.0f, 0.1f),
		GetElementSize(0.75f, 0.8f),
		Alignment::TOP_LEFT,
		true,
		10.0f,
		resolution
		);
	m_elements.push_back(m_slider);

	m_inputLine = std::make_shared<InputLine<int>>(
		focusID,
		GetElementPosition(0.77f, 0.0f),
		GetElementSize(0.13f, 1.0f),
		Alignment::TOP_LEFT,
		3,
		resolution
		);
	m_inputLine->SetOnEnter([this]() {
		this->SaveValue();
		});
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
		this->SaveValue();
	});
	m_btn->SetEnabled(false);
	m_elements.push_back(m_btn);
}

void SliderAndInputLine::SaveValue() const {
	if (!m_btn->IsEnabled()) {
		return;
	}
	std::cout << "New Value: " << m_inputLine->GetValue() << '\n';
	m_btn->SetEnabled(false);
}

SliderAndInputLine::SliderAndInputLine(unsigned int focusID, Vector2 pos,
	Vector2 size, Alignment alignment,
	Vector2 resolution)
	: Scene(pos, size, alignment) {
	GetAlignedCollider(m_pos, m_size, alignment, resolution);
	Initialize(focusID, resolution);
}

void SliderAndInputLine::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);

	if (m_inputLine->HasValueChanced()) {
		m_btn->SetEnabled(true);
	}
}
