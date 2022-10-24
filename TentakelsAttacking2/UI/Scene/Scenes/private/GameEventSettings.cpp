//
// Purpur Tentakel
// 24.10.2022
//

#include "GameEventSettings.h"
#include "Text.h"
#include "CheckBox.h"
#include "Line.h"
#include "GameEventTypes.hpp"
#include <array>
#include <iostream>


void GameEventSettings::Initialize(Vector2 resolution) {

	// Title
	m_elements.push_back(std::make_shared<Text>(
		GetElementPosition(0.5f, 0.0f),
		GetElementSize(0.4f, 0.4f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		0.07f,
		"Events",
		resolution
	));
	// Line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.5f, 0.15f),
		GetElementSize(0.3f, 0.0f),
		Alignment::TOP_MID,
		3.0f,
		resolution
	));

	// Text and Check Box
	float firstRow = 0.25f;
	float row = 0.035f;
	float cbX = 0.51f;
	float textX = 0.49f;
	std::array<std::string, 7> text = {
		"Global",
		"Pirates",
		"Revolts",
		"Renegade ships",
		"Black Hole",
		"Supernova",
		"EngineProblems"
	};

	for (unsigned int i = 0; i < text.size(); ++i) {
		m_elements.push_back(std::make_shared<Text>(
			GetElementPosition(textX, firstRow + row * i * 2),
			GetElementSize(textX, row * 3),
			Alignment::MID_RIGHT,
			Alignment::MID_RIGHT,
			row,
			text.at(i),
			resolution
		));

		auto element = std::make_shared<CheckBox>(
			i + 100,
			GetElementPosition(cbX, firstRow + row * i * 2),
			GetElementSize(0.0f, row*1.5f).y,
			Alignment::MID_LEFT,
			i,
			resolution
		);
		element->SetOnCheck([this](unsigned int ID, bool isChecked) {
			this->SetChecked(ID, isChecked);
			});
		m_elements.push_back(element);
		m_checkBoxes.push_back(element);
	}
}

void GameEventSettings::SetChecked(unsigned int ID, bool isCecked) {
	std::cout << "CHECKED | ID: " << ID << " | " << isCecked << '\n';
}

void GameEventSettings::UpdateElements() {

}

GameEventSettings::GameEventSettings(Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution)
	: Scene(pos, size, alignment) {

	GetAlignedCollider(m_pos, m_size, alignment, resolution);
	Initialize(resolution);
}
