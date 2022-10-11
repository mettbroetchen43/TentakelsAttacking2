//
// Purpur Tentakel
// 11.10.2022
//

#include "HPlayerCollection.h"
#include "UIEvents.hpp"
#include "GenerelEvents.hpp"
#include "AppContext.h"
#include <algorithm>

void PlayerCollection::CheckValidColor(Color& color) {
	if (std::find(m_colors.begin(), m_colors.end(), color)
		== m_colors.end()) {
		auto event = ShowMessagePopUpEvent(
			"Invalid Color",
			"The choosen color does not exist"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		color = GetRemainingColor();
	}
}
void PlayerCollection::CheckRemainingColor(Color& color) {
	if (ContainsValue<Color>(m_playerColors, color)) {
		auto event = ShowMessagePopUpEvent(
			"Invalid Color",
			"The choosen color already exists."
		);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		color = GetRemainingColor();
	}
}
void PlayerCollection::CheckRemainingName(std::string& name) {
	if (ContainsValue<std::string>(m_playerNames, name)) {
		auto event = ShowMessagePopUpEvent(
			"Invalid name",
			"The choosen name already exists."
		);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		name = "Invalid Name " + m_playerNames.size();
	}
}

Color PlayerCollection::GetRemainingColor() {
	for (auto c : m_colors) {
		if (!ContainsValue<Color>(m_playerColors, c)) {
			return c;
		}
	}
	return m_colors.at(0);
}

size_t PlayerCollection::MaxPlayerCount() const {
	return m_maxPlayerCount;
}

void PlayerCollection::AddPlayer(unsigned int ID,
	std::string name, Color color) {

	CheckValidColor(color);
	CheckRemainingColor(color);
	CheckRemainingName(name);
	
	m_playerColors[ID] = color;
	m_playerNames[ID] = name;
}
void PlayerCollection::EditPlayer(unsigned int ID,
	std::string name, Color color) {

	if (m_playerColors.at(ID) != color) {
		CheckValidColor(color);
		CheckRemainingColor(color);
		m_playerColors[ID] = color;
	}

	if (m_playerNames.at(ID) != name) {
		CheckRemainingName(name);
		m_playerNames[ID] = name;
	}
}
void PlayerCollection::RemovePlayer(unsigned int ID) {
	m_playerColors.erase(ID);
	m_playerNames.erase(ID);
}

std::array<Color, 16> PlayerCollection::GetAllColors() const {
	return m_colors;
}
std::unordered_map<unsigned int, Color> PlayerCollection::GetColors() const {
	return m_playerColors;
}
std::unordered_map<unsigned int, std::string> PlayerCollection::GetNames() const {
	return m_playerNames;
}

void PlayerCollection::OnEvent(Event const& event) {

	if (auto const* playerEvent = dynamic_cast<AddPlayerUIEvent const*>(&event)) {
		AddPlayer(
			playerEvent->GetID(),
			playerEvent->GetName(),
			playerEvent->GetColor()
		);
		return;
	}
}
