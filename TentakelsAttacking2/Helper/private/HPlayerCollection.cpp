//
// Purpur Tentakel
// 11.10.2022
//

#include "HPlayerCollection.h"
#include "UIEvents.hpp"
#include "GenerelEvents.hpp"
#include "AppContext.h"
#include <algorithm>
#include <stdexcept>

bool PlayerCollection::ContainsName(std::string const& name) const {
	for (auto const& p : m_playerData) {
		if (p.name == name) {
			return true;
		}
	}

	for (auto const& p : m_npcData) {
		if (p.name == name) {
			return true;
		}
	}

	return false;
}
bool PlayerCollection::ContainsColor(Color color) const {
	for (auto const& p : m_playerData) {
		if (p.color == color) {
			return true;
		}
	}

	for (auto const& p : m_npcData) {
		if (p.color == color) {
			return true;
		}
	}

	return false;
}

void PlayerCollection::CheckValidColor(Color& color) {
	AppContext const& appContext{ AppContext::GetInstance() };
	if (appContext.colors.CheckValidColor(color)) {
		auto const event{ ShowMessagePopUpEvent(
			"Invalid Color",
			"The chosen color does not exist"
		) };
		appContext.eventManager.InvokeEvent(event);
		color = GetPossibleColor();
	}
}
void PlayerCollection::CheckRemainingColor(Color& color) {
	if (ContainsColor(color)) {
		auto const event{ ShowMessagePopUpEvent(
			"Invalid Color",
			"The chosen color already exists."
	) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		color = GetPossibleColor();
	}
}
void PlayerCollection::CheckRemainingName(std::string& name) {

	bool invalidName{ false };

	if (name.empty()) {
		auto const event{ ShowMessagePopUpEvent(
			"Invalid name",
			"No name entered."
		) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		invalidName = true;
	}

	if (ContainsName(name)) {
		auto const event{ ShowMessagePopUpEvent(
			"Invalid name",
			"The chosen name already exists."
		) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		invalidName = true;
	}

	if (invalidName) {
		static size_t invalidNameCounter{ 1 };
		name = "Invalid Name " + std::to_string(invalidNameCounter);
		++invalidNameCounter;
	}
}

PlayerData& PlayerCollection::GetPlayerByIDmut(unsigned int ID) {

	for (auto& p : m_playerData) {
		if (p.ID == ID) {
			return p;
		}
	}

	// skip ncps here because it makes no sense to return them as a player

	throw std::out_of_range("Accessing non existing ID");
}
void PlayerCollection::SortPlayers() {
	std::sort(m_playerData.begin(), m_playerData.end(), SortPlayerByID_ASC);
}

void PlayerCollection::AddPlayer(unsigned int ID,
	std::string name, Color color) {

	CheckValidColor(color);
	CheckRemainingColor(color);
	CheckRemainingName(name);

	m_playerData.emplace_back(ID, name, color);
	SortPlayers();
}
void PlayerCollection::EditPlayer(unsigned int ID,
	std::string name, Color color) {

	PlayerData& playerData{ GetPlayerByIDmut(ID) };

	if (playerData.name != name) {
		CheckRemainingName(name);
		playerData.name = name;
	}

	if (playerData.color != color) {
		CheckValidColor(color);
		CheckRemainingColor(color);
		playerData.color = color;
	}

	SortPlayers();
}
void PlayerCollection::DeletePlayer(unsigned int ID) {
	auto const& toDelete{ GetPlayerByIDmut(ID) };

	m_playerData.erase(
		std::remove(m_playerData.begin(), m_playerData.end(), toDelete
	), m_playerData.end());

	SortPlayers();
}
void PlayerCollection::ResetPlayer(){
	m_playerData.clear();
}

Color PlayerCollection::GetPossibleColor() const {
	AppContext const& appContext{ AppContext::GetInstance() };
	for (auto const c : appContext.colors.GetColors()) {
		if (!ContainsColor(c)) {
			return c;
		}
	}
	return appContext.colors.GetColors().at(0);
}
std::vector<PlayerData> PlayerCollection::GetPlayerData() const {
	return m_playerData;
}

PlayerData PlayerCollection::GetPlayerByID(unsigned int ID) const {

	if (ID == m_defaultPlayer.ID) { return m_defaultPlayer; }

	for (auto const& p : m_playerData) {
		if (p.ID == ID) {
			return p;
		}
	}

	throw std::out_of_range("Accessing non existing ID");
}
PlayerData PlayerCollection::GetPlayerOrNpcByID(unsigned int ID) const {

	for (auto const& p : m_npcData) {
		if (p.ID == ID) {
			return p;
		}
	}
	
	return GetPlayerByID(ID);
}
PlayerData PlayerCollection::GetPlayerByIDOrDefaultPlayer(unsigned int ID) const {

	for (auto const& p : m_playerData) {
		if (ID == p.ID) {
			return p;
		}
	}

	return m_defaultPlayer;
}
PlayerData PlayerCollection::GetPlayerByName(std::string const& name) const {
	for (auto const& p : m_playerData) {
		if (p.name == name) {
			return p;
		}
	}

	throw std::out_of_range("Accessing non existing Name");
}
PlayerData PlayerCollection::GetPlayerByColor(Color color) const {
	for (auto const& p : m_playerData) {
		if (p.color == color) {
			return p;
		}
	}

	throw std::out_of_range("Accessing non existing Color");
}

Color PlayerCollection::GetColorByID(unsigned int ID) const {
	for (auto const& p : m_playerData) {
		if (p.ID == ID) {
			return p.color;
		}
	}
	return WHITE;
}

size_t PlayerCollection::GetPlayerCount() const {
	return m_playerData.size();
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
	if (auto const* playerEvent = dynamic_cast<EditPlayerUIEvent const*>(&event)) {
		EditPlayer(
			playerEvent->GetID(),
			playerEvent->GetName(),
			playerEvent->GetColor()
		);
		return;
	}
	if (auto const* playerEvent = dynamic_cast<DeletePlayerUIEvent const*>(&event)) {
		DeletePlayer(playerEvent->GetID());
		return;
	}
	if (auto const* playerEvent = dynamic_cast<ResetPlayerUIEvent const*>(&event)) {
		ResetPlayer();
		return;
	}
}
