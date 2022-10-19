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
#include <raylib.h>

class PlayerCollection : public EventListener {
private:
	using ColorArray = std::array<Color, 16>;
	size_t m_maxPlayerCount = 7;
	ColorArray m_colors = {
		YELLOW,
		GOLD,
		PINK,
		MAGENTA,
		ORANGE,
		RED,
		MAROON,
		GREEN,
		LIME,
		DARKGREEN,
		SKYBLUE,
		BLUE,
		DARKBLUE,
		PURPLE,
		VIOLET,
		DARKPURPLE,
	};
	std::vector<PlayerData> m_playerData;

	[[nodiscard]] bool ContainsName(std::string const& name) const;
	[[nodiscard]] bool ContainsColor(Color color) const;

	void CheckValidColor(Color& color);
	void CheckRemainingColor(Color& color);
	void CheckRemainingName(std::string& name);

	[[nodiscard]] PlayerData& GetPlayerByID(unsigned int ID);
	void SortPlayers();

public:

	[[nodiscard]] size_t MaxPlayerCount() const;

	void AddPlayer(unsigned int ID,
		std::string name, Color color);
	void EditPlayer(unsigned int ID, std::string name, Color color);
	void DeletePlayer(unsigned int ID);

	[[nodiscard]] ColorArray GetAllColors() const;
	[[nodiscard]] Color GetPossibleColor() const;
	[[nodiscard]] std::vector<PlayerData> GetPlayerData() const;

	[[nodiscard]] PlayerData GetPlayerByID(unsigned int ID) const;
	[[nodiscard]] PlayerData GetPlayerByName(std::string const& name) const;
	[[nodiscard]] PlayerData GetPlayerByColor(Color color) const;
	
	void OnEvent(Event const& event) override;
};