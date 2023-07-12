//
// Purpur Tentakel
// 24.10.2022
//

#include "GameEventSettings.h"
#include "Text.h"
#include "CheckBox.h"
#include "Line.h"
#include "HRandom.h"
#include <array>
#include <utility>
#include <cassert>


void GameEventSettings::Initialize(Vector2 resolution, unsigned int focusID) {

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	// Title
	auto title = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.0f),
		GetElementSize(0.8f, 0.2f),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_MID,
		0.07f,
		appContext.languageManager.Text("ui_game_event_settings_title")
	);
	// title->RenderRectangle(true);
	m_elements.push_back(title);

	// Line
	m_elements.push_back(std::make_shared<Line>(
		GetElementPosition(0.3f, 0.15f),
		GetElementPosition(0.7f, 0.15f),
		resolution,
		3.0f,
		WHITE
	));

	// Text and Check Box
	float const firstRow{ 0.25f };
	float const row     { 0.035f };
	float const cbX     { 0.51f };
	float const textX   { 0.49f };


	for (unsigned int i = 0; i < m_text.size(); ++i) {
		auto displayText = std::make_shared<Text>(
			GetElementPosition(textX, firstRow + row * i * 2),
			GetElementSize(textX + 0.15f, row * 3),
			Alignment::MID_RIGHT,
			resolution,
			Alignment::MID_RIGHT,
			row,
			m_text.at(i).second
		);
		// displayText->RenderRectangle(true);
		m_elements.push_back(displayText);

		auto element = std::make_shared<CheckBox>(
			i + focusID,
			GetElementPosition(cbX, firstRow + row * i * 2),
			GetElementSize(0.0f, row * 1.5f).y,
			Alignment::MID_LEFT,
			resolution,
			i
		);
		element->SetOnCheck([this](unsigned int index, bool isChecked) {
			this->SetChecked(index, isChecked);
		});
		element->SetChecked(appContext.constants.gameEvents.IsFlag(m_text.at(i).first));
		m_checkBoxes.push_back(element);
		m_elements.push_back(element);
	}
}

void GameEventSettings::SetChecked(unsigned int index, bool isChecked) {
	AppContext_ty appContext{ AppContext::GetInstance() };
	appContext.constants.gameEvents.SetFlag(m_text.at(index).first, isChecked);

	assert (m_checkBoxes.size() == m_text.size());

	for (int i = 0; i < m_checkBoxes.size(); ++i) {
		m_checkBoxes.at(i)->SetChecked(appContext.constants.gameEvents.IsFlag(m_text.at(i).first));
	}
}

GameEventSettings::GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution)
	: Scene{ pos, size, alignment, resolution } {

	Initialize(resolution, focusID);
}


void GameEventSettings::SetRandom() {
	Random& random{ Random::GetInstance() };
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	for (auto& c : m_checkBoxes) {
		bool r = random.random(2) == 1;
		if (c->IsChecked() != r) {
			c->SetChecked(r);
		}
	}
}
