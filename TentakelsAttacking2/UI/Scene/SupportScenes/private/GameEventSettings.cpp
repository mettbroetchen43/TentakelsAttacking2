//
// Purpur Tentakel
// 24.10.2022
//

#include "GameEventSettings.h"
#include "Text.h"
#include "CheckBox.h"
#include "Line.h"
#include "HGameEventTypes.hpp"
#include "AppContext.h"
#include "HRandom.h"
#include <array>
#include <iostream>


void GameEventSettings::Initialize(Vector2 resolution, unsigned int focusID) {

	// Title
	auto title = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.0f),
		GetElementSize(0.8f, 0.2f),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_MID,
		0.07f,
		"Events"
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
	std::array<std::string, 7> const text{
		"Global",
		"Pirates",
		"Revolts",
		"Renegade ships",
		"Black Hole",
		"Supernova",
		"Engine Problems"
	};

	for (unsigned int i = 0; i < text.size(); ++i) {
		auto displayText = std::make_shared<Text>(
			GetElementPosition(textX, firstRow + row * i * 2),
			GetElementSize(textX + 0.15f, row * 3),
			Alignment::MID_RIGHT,
			resolution,
			Alignment::MID_RIGHT,
			row,
			text.at(i)
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
		element->SetOnCheck([this](unsigned int ID, bool isChecked) {
			this->SetChecked(ID, isChecked);
			});
		m_checkBoxes.push_back(element);
		m_elements.push_back(element);
	}
}

void GameEventSettings::SetChecked(unsigned int ID, bool isChecked) {
	UpdateCheckGameEvent const event{
		static_cast<HGameEventType>(ID),
		isChecked
	};
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

void GameEventSettings::UpdateElements(UpdateCheckGameEventsUI const* event) {

	auto const types{ event->GetTypes() };

	for (auto const& [type, b] : *types) {
		for (auto checkBox : m_checkBoxes) {
			auto const cbType{ static_cast<HGameEventType>(checkBox->GetID()) };
			if (cbType == type) {
				checkBox->SetChecked(b);
				continue;
			}
		}
	}

	SetGlobalCheckbox();
}
void GameEventSettings::SetGlobalCheckbox(){
	CheckBox_ty globalCheckbox{ nullptr };
	bool check{ true };
	bool value{ false };

	for (size_t i = 0; i < m_checkBoxes.size(); ++i) {
		auto const cbTypeI{ static_cast<HGameEventType>(m_checkBoxes.at(i)->GetID()) };
		if (cbTypeI == HGameEventType::GLOBAL) {
			globalCheckbox = m_checkBoxes.at(i);
			continue;
		}
		value = m_checkBoxes.at(i)->IsChecked();
		for (size_t j = i; j < m_checkBoxes.size(); ++j) {
			auto cbTypeJ{ static_cast<HGameEventType>(m_checkBoxes.at(i)->GetID()) };
			if (cbTypeJ == HGameEventType::GLOBAL) {
				continue;
			}
			if (m_checkBoxes.at(i)->IsChecked()
				!= m_checkBoxes.at(j)->IsChecked()) {
				check = false;
				goto found;
			}
		}
	}

found:
	if (check) {
		globalCheckbox->SetChecked(value);
	}
	else {
		globalCheckbox->SetChecked(false);
	}
}

GameEventSettings::GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution)
	: Scene{ pos, size, alignment, resolution } {
	AppContext_ty appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);

	Initialize(resolution, focusID);

	InitialCheckGameEventDataEvent const event;
	appContext.eventManager.InvokeEvent(event);
}
GameEventSettings::~GameEventSettings() {
	AppContext::GetInstance().eventManager.RemoveListener(this);
}

void GameEventSettings::OnEvent(Event const& event) {

	if (auto const* UpdateEvent = dynamic_cast<UpdateCheckGameEventsUI const*>(&event)) {
		UpdateElements(UpdateEvent);
		return;
	}
}

void GameEventSettings::SetRandom() {
	Random& random{ Random::GetInstance() };
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	for (auto& c : m_checkBoxes) {
		if (c->GetID() == 0) { continue; } ///< id 0 is the gloabl check box

		bool r = random.random(2) == 1;
		if (c->IsChecked() != r) {
			UpdateCheckGameEvent const event{
				static_cast<HGameEventType>(c->GetID()),
				r
			};
			appContext.eventManager.InvokeEvent(event);
		}
	}

	SetGlobalCheckbox();
}
