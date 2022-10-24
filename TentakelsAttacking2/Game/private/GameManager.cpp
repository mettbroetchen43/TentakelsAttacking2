//
// PurpurTentakel
// 10.08.22
//

#include "GameManager.h"
#include "AppContext.h"

bool GameManager::ValidAddPlayer() const {
	return AppContext::GetInstance().playerCollection.MaxPlayerCount()
		> m_players.size();
}
unsigned int GameManager::GetNextID() const {
	unsigned int nextID = 1;
	while (true) {
		bool freeID = true;
		for (auto p : m_players) {
			if (p->GetID() == nextID) {
				freeID = false;
				break;
			}
		}

		if (freeID) {
			return nextID;
		}

		++nextID;
	}
}

bool GameManager::IsExistingID(unsigned int ID) const {
	for (auto const& p : m_players) {
		if (p->GetID() == ID) {
			return true;
		}
	}
	return false;
}

void GameManager::AddPlayer(AddPlayerEvent const* event) {
	if (!ValidAddPlayer()) {
		auto UIEvent = ShowMessagePopUpEvent(
			"Max Player",
			"No more Player slots are available"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(UIEvent);
		return;
	}

	unsigned int newID = GetNextID();
	auto player = std::make_shared<Player>(
		newID,
		PlayerType::HUMAN
		);
	m_players.push_back(player);

	auto AddEvent = AddPlayerUIEvent(
		newID,
		event->GetName(),
		event->GetColor()
	);
	AppContext::GetInstance().eventManager.InvokeEvent(AddEvent);
}
void GameManager::EditPlayer(EditPlayerEvent const* event) const {
	
	if (!IsExistingID(event->GetID())) {
		auto UIEvent = ShowMessagePopUpEvent(
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(UIEvent);
		return;
	}

	auto editEvent = EditPlayerUIEvent(
		event->GetID(),
		event->GetName(),
		event->GetColor()
	);
	AppContext::GetInstance().eventManager.InvokeEvent(editEvent);
}
void GameManager::DeletePlayer(DeletePlayerEvent const* event) {

	std::shared_ptr<Player> toDelete = nullptr;
	for (auto& p : m_players) {
		if (p->GetID() == event->GetID()) {
			toDelete = p;
			break;
		}
	}

	if (!toDelete) {
		auto messageEvent = ShowMessagePopUpEvent(
			"Invalid ID",
			"ID " + std::to_string(event->GetID()) + " is not existing"
		);
		AppContext::GetInstance().eventManager.InvokeEvent(messageEvent);
		return;
	}

	m_players.erase(std::remove(
		m_players.begin(), m_players.end(), toDelete),
		m_players.end());

	auto deleteEvent = DeletePlayerUIEvent(event->GetID());
	AppContext::GetInstance().eventManager.InvokeEvent(deleteEvent);
}

void GameManager::SetGameEventActive(UpdateCheckGameEvent const* event) {
	if (event->GetType() == GameEventType::GLOBAL) {
		for (auto e : settableGameEventTypes) {
			m_gameEvents[e] = event->GetIsChecked();
		}
	}
	else {
		m_gameEvents[event->GetType()] = event->GetIsChecked();
	}

	auto updateEvent = UpdateCheckGameEventsUI(&m_gameEvents);
	AppContext::GetInstance().eventManager.InvokeEvent(updateEvent);
}

GameManager::GameManager() {
	AppContext::GetInstance().eventManager.AddListener(this);
	for (auto e : settableGameEventTypes) {
		m_gameEvents[e] = true;
	}
}

std::vector<std::shared_ptr<Player>>& GameManager::GetPlayers() {
	return m_players;
}
std::vector<std::shared_ptr<Player>> const& GameManager::GetPlayers() const {
	return m_players;
}

void GameManager::Update() {
	m_galaxy.PreUpdate(); // bevor main update -> z.B. move
	m_galaxy.Update();  // main update
	m_galaxy.PostUpdate(); // debug Print
}
void GameManager::OnEvent(Event const& event) {

	// Player
	if (auto const* playerEvent = dynamic_cast<AddPlayerEvent const*>(&event)) {
		AddPlayer(playerEvent);
		return;
	}
	if (auto const* playerEvent = dynamic_cast<EditPlayerEvent const*>(&event)) {
		EditPlayer(playerEvent);
		return;
	}
	if (auto const* playerEvent = dynamic_cast<DeletePlayerEvent const*>(&event)) {
		DeletePlayer(playerEvent);
		return;
	}

	// Game Events
	if (auto const* GameEvent = dynamic_cast<UpdateCheckGameEvent const *>(&event)) {
		SetGameEventActive(GameEvent);
		return;
	}
	if (auto const* GameEvent = dynamic_cast<InitialCheckGameEventDataEvent const*>(&event)) {
		auto updateEvent = UpdateCheckGameEventsUI(&m_gameEvents);
		AppContext::GetInstance().eventManager.InvokeEvent(updateEvent);
		return;
	}
}
