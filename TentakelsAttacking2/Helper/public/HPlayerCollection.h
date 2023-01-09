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

/**
 * contains and manage all the non logic player data.
 */
class PlayerCollection final : public EventListener {
private:
	std::vector<PlayerData> m_playerData; ///< contains player data
	PlayerData m_defaultPlayer = { 0,"no player", WHITE }; ///< contains default player witch is return if no other player is found.

	/**
	 * checks if name already exsists
	 */
	[[nodiscard]] bool ContainsName(std::string const& name) const;
	/**
	 * checks if color already exsists
	 */
	[[nodiscard]] bool ContainsColor(Color color) const;

	/**
	 * checks if color is valid.
	 * if not: valid color is deplayed and an popup is generated.
	 */
	void CheckValidColor(Color& color);
	/**
	 * checks if color is stoll free.
	 * if no: color free is deployed and an popup is generated.
	 */
	void CheckRemainingColor(Color& color);
	/**
	 * checks if name is still free and not empty.
	 * if not: a default name in deplayed and an popup is generated.
	 */
	void CheckRemainingName(std::string& name);

	/**
	 * returns the player by id muable.
	 */
	[[nodiscard]] PlayerData& GetPlayerByIDmut(unsigned int ID);
	/**
	 * sorty the player by is ASC.
	 */
	void SortPlayers();

	/**
	 * should only be called by event.
	 * adds a new player after validation.
	 */
	void AddPlayer(unsigned int ID,
		std::string name, Color color);
	/**
	 * should only be called by event.
	 * edits a new player after validation.
	 */
	void EditPlayer(unsigned int ID, std::string name, Color color);
	/**
	 * should only be called by event.
	 * deletes a new player after validation.
	 */
	void DeletePlayer(unsigned int ID);
	/**
	 * should only be called by event.
	 * clears all player exept the default player.
	 */
	void ResetPlayer();

public:
	/**
	 * return a vector with the colors that are still free.
	 */
	[[nodiscard]] Color GetPossibleColor() const;
	/**
	 * returns a vector with all players exept the default player.
	 */
	[[nodiscard]] std::vector<PlayerData> GetPlayerData() const;

	/**
	 * returns a player by id.
	 * if the id is 0 the default player will be returned.
	 */
	[[nodiscard]] PlayerData GetPlayerByID(unsigned int ID) const;
	/**
	 * returns a player by id.
	 * if no matching player was found, the default player gets returned.
	 */
	[[nodiscard]] PlayerData GetPlayerByIDOrDefaultPlayer(unsigned int ID) const;
	/**
	 * returns a player by name.
	 */
	[[nodiscard]] PlayerData GetPlayerByName(std::string const& name) const;
	/**
	 * returns a player by color.
	 */
	[[nodiscard]] PlayerData GetPlayerByColor(Color color) const;

	/**
	 * returns the color by id.
	 * if the id is not existing white will be returned.
	 */
	[[nodiscard]] Color GetColorByID(unsigned int ID) const;

	/**
	 * returns the current player count.
	 */
	[[nodiscard]] size_t GetPlayerCount() const;

	/**
	 * received all events an alls the function whithin this object.
	 */
	void OnEvent(Event const& event) override;
};