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

GameManager::GameManager() {
	AppContext::GetInstance().eventManager.AddListener(this);
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

	if (auto const* playerEvent = dynamic_cast<AddPlayerEvent const*>(&event)) {
		AddPlayer(playerEvent);
		return;
	}
}
