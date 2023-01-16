//
// Purpur Tentakel
// 10.11.2022
//

#pragma once
#include "MainEvent.hpp"
#include <string>
#include <raylib.h>

enum class GameEventType;
class Galaxy;

/**
 * general event to provide player name and color.
 */
class PlayerEvent : public Event {
private:
	std::string m_name;
	Color m_color;

public:
	PlayerEvent(std::string const& name, Color color)
		: m_name(name), m_color(color){ }

	[[nodiscard]] std::string GetName() const {
		return m_name;
	}
	[[nodiscard]] Color GetColor() const {
		return m_color;
	}
};
/**
 * general event to provide player ID, name and color.
 */
class PlayerWithIDEvent : public PlayerEvent {
private:
	unsigned int m_ID;

public:
	PlayerWithIDEvent(unsigned int ID, std::string const& name, Color color)
		: PlayerEvent(name, color), m_ID(ID) { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};

/**
 * use this to add a player in the locig.
 */
class AddPlayerEvent final : public PlayerEvent {
public:
	using PlayerEvent::PlayerEvent;
};
/**
 * use this to edit a player in the locig.
 */
class EditPlayerEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
/**
 * use this to delete a player by id in the locig.
 */
class DeletePlayerEvent final : public Event {
private:
	unsigned int m_ID;
public:
	DeletePlayerEvent(unsigned int ID)
		:m_ID(ID) { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
/**
 * use this to remove all player in locig.
 */
class ResetPlayerEvent final : public Event { };

/**
 * "callbackevent" from AddPlayerEvent.
 * use this so add a player in PlayerCollection
 */
class AddPlayerUIEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
/**
 * "callbackevent" from EditPlayerEvent.
 * use this to edit a player in PlayerCollection
 */
class EditPlayerUIEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
/**
 * "callbackevent" from DeletePlayerEvent.
 * use this to delete a player in PlayerCollection
 */
class DeletePlayerUIEvent final : public Event {
private:
	unsigned int m_ID;
public:
	DeletePlayerUIEvent(unsigned int ID)
		:m_ID(ID) { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
/**
 * "callbackevent" from ResetPlayerEvent.
 * use this remove all player from PlayerCollection
 */
class ResetPlayerUIEvent final : public Event { };

/**
 * general event to provide a player id.
 */
class PlayerIDEvent : public Event {
private:
	unsigned int m_ID;

public:
	PlayerIDEvent(unsigned int ID)
		:m_ID(ID) { }
	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
/**
 * use this to update the current player id in the UI.
 */
class UpdateCurrentPlayerIDEvent final : public PlayerIDEvent {
public:
	using PlayerIDEvent::PlayerIDEvent;
};
/**
 * use this to update the next player id in the UI.
 */
class UpdateNextPlayerIDEvent final : public PlayerIDEvent {
public:
	using PlayerIDEvent::PlayerIDEvent;
};

/**
 * use this to trigger the logic to evaluate the next turn or round if no player remaining.
 */
class TriggerNextTurnEvent final : public Event  { };
/**
 * use this to trigger the ui to show the next turn.
 */
class ShowNextTurnEvent final : public Event { };
/**
 * use this to trigger the ui to show the next round.
 */
class ShowNextRoundEvent final : public Event { };

/**
 * use this to trigger the logic to validate the Player count.
 * return an ValidatePlayerCountResultEvent.
 */
class ValidatePlayerCountEvent final : public Event { };
/**
 * use this to return the value of ValidatePlayerCountEvent.
 * ui should listen to that.
 */
class ValidatePlayerCountResultEvent final : public Event {
private:
	bool m_validPlayerCount;

public:
	ValidatePlayerCountResultEvent(bool validPlayerCount)
		: m_validPlayerCount(validPlayerCount) { }

	[[nodiscard]] bool GetValid() const {
		return m_validPlayerCount;
	}
};

/**
 * use this to trigger the logic to start the game.
 */
class StartGameEvent final : public Event { };

/**
 * use this to trigger the logic to updating the game events.
 * returns a UpdateCheckGameEventsUI.
 */
class UpdateCheckGameEvent final : public Event {
private:
	GameEventType m_type;
	bool m_isChecked;

public:
	UpdateCheckGameEvent(GameEventType type, bool isChecked)
		: m_type(type), m_isChecked(isChecked) {}

	[[nodiscard]] GameEventType GetType() const {
		return m_type;
	}
	[[nodiscard]] bool GetIsChecked() const {
		return m_isChecked;
	}
};
/**
 * use this to trigger the ui to update the game events.
 */
class UpdateCheckGameEventsUI final : public Event {
private:
	using Map = std::unordered_map<GameEventType, bool>const*;
	Map m_types;

public:
	UpdateCheckGameEventsUI(Map types)
		: m_types(types) { }

	[[nodiscard]] Map GetTypes() const {
		return m_types;
	}
};
/**
 * use this to trigger the logic to return the current state of the game events.
 * returns a UpdateCheckGameEventsUI.
 */
class InitialCheckGameEventDataEvent final : public Event { };

/**
 * use this to trigger the constants to update the target last round. 
 */
class SetCurrentLastRoundEvent final : public Event {
private:
	int m_lastRound;

public:
	SetCurrentLastRoundEvent(int lastRound)
		:m_lastRound(lastRound) { }

	[[nodiscard]] int GetLastRound() const {
		return m_lastRound;
	}
};

/**
 * use this to trigger the logic to generate a new galaxy.
 */
class GenerateGalaxyEvent final : public Event { };
/**
 * use this to trigger the logic to generate a new show galaxy.
 */
class GalaxyGeneratedUIEvent final : public Event { };

/**
 * use this to trigger the logic to return a galaxy pointer.
 * returns a SendGalaxyPointerEvent.
 */
class GetGalaxyPointerEvent final : public Event { };
/**
 * use this to trigger the logic to return a show galaxy pointer.
 * returns a SendGalaxyPointerEvent.
 */
class GetShowGalaxyPointerEvent final : public Event { };
/**
 * sends a galaxy pointer to the ui.
 */
class SendGalaxyPointerEvent final : public Event {
private:
	Galaxy const *const m_galaxy;

public:
	SendGalaxyPointerEvent(Galaxy const *const galaxy)
		: m_galaxy(galaxy) { }

	[[nodiscard]] Galaxy const *const GetGalaxy() const {
		return m_galaxy;
	}
};
