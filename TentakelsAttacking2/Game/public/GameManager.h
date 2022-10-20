//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "Player.h"
#include "Galaxy.h"
#include "EventListener.hpp"
#include "UIEvents.hpp"
#include "GenerelEvents.hpp"
#include <vector>

class GameManager : public EventListener {
private:
	std::vector<std::shared_ptr<Player>> m_players;
	Galaxy m_galaxy;

	[[nodiscard]] bool ValidAddPlayer() const;
	[[nodiscard]] unsigned int GetNextID() const;
	[[nodiscard]] bool IsExistingID(unsigned int ID) const;

	void AddPlayer(AddPlayerEvent const* event);
	void EditPlayer(EditPlayerEvent const* event) const;
	void DeletePlayer(DeletePlayerEvent const* event);

public:
	GameManager();

	[[nodiscard]] std::vector<std::shared_ptr<Player>>& GetPlayers();
	[[nodiscard]] std::vector<std::shared_ptr<Player>> const& GetPlayers() const;

	void Update();

	void OnEvent(Event const& event) override;
};

