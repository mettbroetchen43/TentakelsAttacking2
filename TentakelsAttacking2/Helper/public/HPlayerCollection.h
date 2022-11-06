//
// Purpur Tentakel
// 11.10.2022
//

#pragma once
#include "EventListener.hpp"
#include "HGeneral.h"
#include "HPlayerData.hpp"
#include <string>
#include <array>
#include <vector>


class PlayerCollection final : public EventListener {
private:
	std::vector<PlayerData> m_playerData;

	[[nodiscard]] bool ContainsName(std::string const& name) const;
	[[nodiscard]] bool ContainsColor(Color color) const;

	void CheckValidColor(Color color);
	void CheckRemainingColor(Color& color);
	void CheckRemainingName(std::string& name);

	[[nodiscard]] PlayerData& GetPlayerByID(unsigned int ID);
	void SortPlayers();

	void AddPlayer(unsigned int ID,
		std::string name, Color color);
	void EditPlayer(unsigned int ID, std::string name, Color color);
	void DeletePlayer(unsigned int ID);
	void ResetPlayer();

public:
	[[nodiscard]] Color GetPossibleColor() const;
	[[nodiscard]] std::vector<PlayerData> GetPlayerData() const;

	[[nodiscard]] PlayerData GetPlayerByID(unsigned int ID) const;
	[[nodiscard]] PlayerData GetPlayerByName(std::string const& name) const;
	[[nodiscard]] PlayerData GetPlayerByColor(Color color) const;
	
	void OnEvent(Event const& event) override;
};