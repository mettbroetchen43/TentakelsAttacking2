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

class AddPlayerEvent final : public PlayerEvent {
public:
	using PlayerEvent::PlayerEvent;
};
class EditPlayerEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
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
class ResetPlayerEvent final : public Event { };

class AddPlayerUIEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
class EditPlayerUIEvent final : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
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
class ResetPlayerUIEvent final : public Event { };

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
class GetCurrentPlayerIDEvent final : public Event { };
class SendCurrentPlayerIDEvent final : public PlayerIDEvent {
	using PlayerIDEvent::PlayerIDEvent;
};
class GetNextPlayerIDEvent final : public Event { };
class SendNextPlayerIDEvent final : public PlayerIDEvent {
	using PlayerIDEvent::PlayerIDEvent;
};

class ValidatePlayerCountEvent final : public Event { };
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

class StartGameEvent final : public Event { };

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
class InitialCheckGameEventDataEvent final : public Event { };

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

class GenerateGalaxyEvent final : public Event { };
class GalaxyGeneratedUIEvent final : public Event { };

class GetGalaxyPointerEvent final : public Event { };
class GetShowGalaxyPointerEvent final : public Event { };
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
