//
// Purpur Tentakel
// 06.11.2022
//

#pragma once
#include <memory>
#include "Vec2.hpp"
#include "LogicUpdate.hpp"

class Player;

class SpaceObject /*: public LogicUpdate */ {
protected:
	using vec2pos = Vec2<size_t>;
	unsigned int m_ID;
	size_t m_ships = 0;
	vec2pos m_position;
	std::shared_ptr<Player> m_player;

public:
	SpaceObject(unsigned int ID, vec2pos position, std::shared_ptr<Player> player);
	SpaceObject(unsigned int ID, vec2pos position, size_t ships, std::shared_ptr<Player> player);
	virtual ~SpaceObject() = default;

	[[nodiscard]] unsigned int GetID() const;

	void SetPlayer(std::shared_ptr<Player> player);
	[[nodiscard]] std::shared_ptr<Player> GetPlayer() const;

	void SetPos(vec2pos pos);
	[[nodiscard]] vec2pos GetPos() const;

	friend size_t operator+ (SpaceObject const& object, size_t ships);
	friend size_t operator+ (size_t ships, SpaceObject const& object);
	friend size_t operator+ (SpaceObject const& lhs, SpaceObject const& rhs);

	friend size_t operator- (SpaceObject const& object, size_t ships);
	friend size_t operator- (size_t ships, SpaceObject const& object);
	friend size_t operator- (SpaceObject const& lhs, SpaceObject const& rhs);

	friend bool operator< (SpaceObject const& object, size_t ships);
	friend bool operator< (size_t ships, SpaceObject const& object);
	friend bool operator< (SpaceObject const& lhs, SpaceObject const& rhs);

	friend bool operator<= (SpaceObject const& object, size_t ships);
	friend bool operator<= (size_t ships, SpaceObject const& object);
	friend bool operator<= (SpaceObject const& lhs, SpaceObject const& rhs);

	friend bool operator> (SpaceObject const& object, size_t ships);
	friend bool operator> (size_t ships, SpaceObject const& object);
	friend bool operator> (SpaceObject const& lhs, SpaceObject const& rhs);

	friend bool operator>= (SpaceObject const& object, size_t ships);
	friend bool operator>= (size_t ships, SpaceObject const& object);
	friend bool operator>= (SpaceObject const& lhs, SpaceObject const& rhs);

	SpaceObject& operator+=(size_t ships);
	SpaceObject& operator+=(SpaceObject const& object);

	SpaceObject& operator-=(size_t ships);
	SpaceObject& operator-=(SpaceObject const& object);

	[[nodiscard]] bool operator== (SpaceObject const& other) const;
};

[[nodiscard]] size_t operator+ (SpaceObject const& object, size_t ships);
[[nodiscard]] size_t operator+ (size_t ships, SpaceObject& object);
[[nodiscard]] size_t operator+ (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] size_t operator- (SpaceObject const& object, size_t ships);
[[nodiscard]] size_t operator- (size_t ships, SpaceObject const& object);
[[nodiscard]] size_t operator- (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator< (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator< (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator< (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator<= (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator<= (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator<= (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator> (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator> (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator> (SpaceObject const& lhs, SpaceObject const& rhs);

[[nodiscard]] bool operator>= (SpaceObject const& object, size_t ships);
[[nodiscard]] bool operator>= (size_t ships, SpaceObject const& object);
[[nodiscard]] bool operator>= (SpaceObject const& lhs, SpaceObject const& rhs);
