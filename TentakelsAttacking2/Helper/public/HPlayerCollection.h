//
// Purpur Tentakel
// 11.10.2022
//

#pragma once
#include "EventListener.hpp"
#include "HGeneral.h"
#include <unordered_map>
#include <array>
#include <raylib.h>


class PlayerCollection : public EventListener {
private:
	size_t m_maxPlayerCount = 7;
	std::array<Color, 16> m_colors = {
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
	std::unordered_map<unsigned int, Color> m_playerColors;
	std::unordered_map<unsigned int, std::string> m_playerNames;

	template<typename T>
	[[nodiscard]] bool ContainsValue(
		std::unordered_map<unsigned int, T> map, T value) {
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

	[[nodiscard]] Color GetRemainingColor();

public:

	[[nodiscard]] size_t MaxPlayerCount() const;

	void AddPlayer(unsigned int ID,
		std::string name, Color color);
	void EditPlayer(unsigned int ID, std::string name, Color color);
	void RemovePlayer(unsigned int ID);

	[[nodiscard]] std::array<Color, 16> GetAllColors() const;
	[[nodiscard]] std::unordered_map<unsigned int, Color> GetColors() const;
	[[nodiscard]] std::unordered_map<unsigned int, std::string> GetNames() const;
	
	void OnEvent(Event const& event) override;
};