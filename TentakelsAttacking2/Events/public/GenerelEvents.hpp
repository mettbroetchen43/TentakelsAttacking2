//
// Purpur Tentakel
// 10.11.2022
//

#pragma once
#include "MainEvent.hpp"
#include <string>
#include <raylib.h>

enum class GameEventType;

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

class AddPlayerEvent : public PlayerEvent {
public:
	using PlayerEvent::PlayerEvent;
};
class EditPlayerEvent : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
class DeletePlayerEvent : public Event {
private:
	unsigned int m_ID;
public:
	DeletePlayerEvent(unsigned int ID)
		:m_ID(ID) { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
class ResetPlayerEvent : public Event { };

class AddPlayerUIEvent : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
class EditPlayerUIEvent : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
class DeletePlayerUIEvent : public Event {
private:
	unsigned int m_ID;
public:
	DeletePlayerUIEvent(unsigned int ID)
		:m_ID(ID) { }

	[[nodiscard]] unsigned int GetID() const {
		return m_ID;
	}
};
class ResetPlayerUIEvent : public Event { };

class ValidatePlayerCountEvent : public Event { };
class ValidatePlayerCountResultEvent : public Event {
private:
	bool m_validPlayerCount;

public:
	ValidatePlayerCountResultEvent(bool validPlayerCount)
		: m_validPlayerCount(validPlayerCount) { }

	[[nodiscard]] bool GetValid() const {
		return m_validPlayerCount;
	}
};

class UpdateCheckGameEvent : public Event {
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
class UpdateCheckGameEventsUI : public Event {
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
class InitialCheckGameEventDataEvent : public Event { };

class SetCurrentLastRoundEvent : public Event {
private:
	int m_lastRound;

public:
	SetCurrentLastRoundEvent(int lastRound)
		:m_lastRound(lastRound) { }

	[[nodiscard]] int GetLastRound() const {
		return m_lastRound;
	}
};
