//
// Purpur Tentakel
// 10.11.2022
//

#pragma once
#include "MainEvent.hpp"
#include <string>
#include <raylib.h>

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
class AddPlayerEvent : public PlayerEvent {
public:
	using PlayerEvent::PlayerEvent;
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
class AddPlayerWithIDEvent : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
class EditPlayerEvent : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};
class DeletePlayerEvent : public PlayerWithIDEvent {
public:
	using PlayerWithIDEvent::PlayerWithIDEvent;
};