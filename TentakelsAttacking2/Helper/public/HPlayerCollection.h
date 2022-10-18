//
// Purpur Tentakel
// 11.10.2022
//

#pragma once
#include "EventListener.hpp"
#include "HGeneral.h"
#include <map>
#include <string>
#include <array>
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
	std::map<unsigned int, Color> m_playerColors;
	std::map<unsigned int, std::string> m_playerNames;

	template<typename T>
	[[nodiscard]] bool ContainsValue(
		std::map<unsigned int, T> map, T value) const {
		for (auto [ID, element] : map) {
			if (element == value) {
				return true;
			}
		}
		return false;
	}

	void CheckValidColor(Color& color);
	void CheckRemainingColor(Color& color);
	void CheckRemainingName(std::string& name);

public:

	[[nodiscard]] size_t MaxPlayerCount() const;

	void AddPlayer(unsigned int ID,
		std::string name, Color color);
	void EditPlayer(unsigned int ID, std::string name, Color color);
	void DeletePlayer(unsigned int ID);

	[[nodiscard]] ColorArray GetAllColors() const;
	[[nodiscard]] Color GetPossibleColor() const;
	[[nodiscard]] std::map<unsigned int, Color> GetColors() const;
	[[nodiscard]] std::map<unsigned int, std::string> GetNames() const;
	
	void OnEvent(Event const& event) override;
};