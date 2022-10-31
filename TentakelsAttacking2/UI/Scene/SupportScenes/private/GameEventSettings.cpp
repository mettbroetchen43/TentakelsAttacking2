//
// Purpur Tentakel
// 24.10.2022
//

#include "GameEventSettings.h"
#include "Text.h"
#include "CheckBox.h"
#include "Line.h"
#include "GameEventTypes.hpp"
#include "AppContext.h"
#include <array>


void GameEventSettings::Initialize(Vector2 resolution, unsigned int focusID) {

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
		"Engine Problems"
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
			i + focusID,
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
	auto event = UpdateCheckGameEvent(
		static_cast<GameEventType>(ID),
		isCecked
	);
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

void GameEventSettings::UpdateElements(UpdateCheckGameEventsUI const* event) {

	auto types = event->GetTypes();

	for (auto const& [type, b] : *types) {
		for (auto checkBox : m_checkBoxes) {
			auto cbType = static_cast<GameEventType>(checkBox->GetID());
			if (cbType == type) {
				checkBox->SetChecked(b);
				continue;
			}
		}
	}

	std::shared_ptr<CheckBox> gloablCheckbox = nullptr;
	bool check = true;
	bool value = false;

	for (size_t i = 0; i < m_checkBoxes.size(); ++i) {
		auto cbTypei = static_cast<GameEventType>(m_checkBoxes.at(i)->GetID());
		if (cbTypei == GameEventType::GLOBAL) {
			gloablCheckbox = m_checkBoxes.at(i);
			continue;
		}
		value = m_checkBoxes.at(i)->IsChecked();
		for (size_t j = i; j < m_checkBoxes.size(); ++j) {
			auto cbTypej = static_cast<GameEventType>(m_checkBoxes.at(i)->GetID());
			if (cbTypej == GameEventType::GLOBAL) {
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
		gloablCheckbox->SetChecked(value);
	}
	else {
		gloablCheckbox->SetChecked(false);
	}

}

GameEventSettings::GameEventSettings(unsigned int focusID, Vector2 pos, Vector2 size,
	Alignment alignment, Vector2 resolution)
	: Scene(pos, size, alignment) {
	AppContext& appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);

	GetAlignedCollider(m_pos, m_size, alignment, resolution);
	Initialize(resolution, focusID);

	auto event = InitialCheckGameEventDataEvent();
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
