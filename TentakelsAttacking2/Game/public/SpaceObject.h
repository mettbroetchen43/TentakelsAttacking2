//
// Purpur Tentakel
// 06.11.2022
//

#pragma once
#include <memory>
#include "Vec2.hpp"
#include <string>
#include <memory>

class Player;
class Galaxy;

/**
 * the basic space object, that every element in the galaxy is implementing.
 */
class SpaceObject{
protected:
	using vec2pos = Vec2<int>; ///< the position type
	unsigned int m_ID; ///< contains the unique id
	size_t m_ships; ///< contains the current amount of ships
	vec2pos m_position; ///< contains the absolute position within the galaxy
	std::shared_ptr<Player> m_player; ///< contains a pointer to a player who owns the object

public:
	/**
	 * ctor without ships.
	 * only initialisation
	 */
	SpaceObject(unsigned int ID, vec2pos position, std::shared_ptr<Player> player);
	/**
	 * ctor.
	 * only initialisation.
	 */
	SpaceObject(unsigned int ID, vec2pos position, size_t ships, std::shared_ptr<Player> player);
	/**
	 * virtual dtor to provide a default one.
	 */
	virtual ~SpaceObject() = default;

	/**
	 * updates the SpaceObject.
 	 */
	virtual void Update(Galaxy const* galaxy) = 0; 

	/**
	 * returns the unique id.
	 */
	[[nodiscard]] unsigned int GetID() const;

	/**
	 * sets a new player as owner of the object.
	 */
	void SetPlayer(std::shared_ptr<Player> player);
	/**
	 * returns the current player who owns the object.
	 */
	[[nodiscard]] std::shared_ptr<Player> GetPlayer() const;

	/**
	 * sets a new position in the galaxy.
	 */
	void SetPos(vec2pos pos);
	/**
	 * returns the current position.
	 */
	[[nodiscard]] vec2pos GetPos() const;

	/**
	 * sets a new ship count.
	 * only if necessary.
	 */
	void SetShipCount(size_t shipCount);
	/**
	 * returns the current ship Count
	 */
	[[nodiscard]] size_t GetShipCount() const;


	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] virtual bool IsPlanet() const;
	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] virtual bool IsFleet() const;
	/**
	 * returns if the current space object is a planet.
	 */
	[[nodiscard]] virtual bool IsTargetPoint() const;

	/**
	 * adds and returns the ship count of an object and a number.
	 */
	friend size_t operator+ (SpaceObject const& object, size_t ships);
	/**
	 * adds and returns the ship count of an object and a number.
	 */
	friend size_t operator+ (size_t ships, SpaceObject const& object);
	/**
	 * adds and returns two ship counts.
	 */
	friend size_t operator+ (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * substracts and returns the ship count of an object and a number.
	 */
	friend size_t operator- (SpaceObject const& object, size_t ships);
	/**
	 * substracts and returns the ship count of an object and a number.
	 */
	friend size_t operator- (size_t ships, SpaceObject const& object);
	/**
	 * substracts and returns two ship counts.
	 */
	friend size_t operator- (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is smaller than the number. 
	 */
	friend bool operator< (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is smaller than the ship count.
	 */
	friend bool operator< (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count smaller than the rhs ship count.
	 */
	friend bool operator< (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is smaller than or equal to the number.
	 */
	friend bool operator<= (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is smaller than or equal to the ship count.
	 */
	friend bool operator<= (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count smaller than or equal to the rhs ship count.
	 */
	friend bool operator<= (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is greater than the number.
	 */
	friend bool operator> (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is greater than the ship count.
	 */
	friend bool operator> (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count greater than the rhs ship count.
	 */
	friend bool operator> (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the ship count is greater than or equal to the number.
	 */
	friend bool operator>= (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is greater than or equal to the ship count.
	 */
	friend bool operator>= (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs ship count greater than or equal to the rhs ship count.
	 */
	friend bool operator>= (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * add an amount of ships to the ship count.
	 */
	SpaceObject& operator+=(size_t ships);
	/**
	 * add an other ship count to the ship count.
	 */
	SpaceObject& operator+=(SpaceObject const& object);

	/**
	 * substract an amount of ships to the ship count.
	 */
	SpaceObject& operator-=(size_t ships);
	/**
	 * substract an other ship count to the ship count.
	 */
	SpaceObject& operator-=(SpaceObject const& object);

	/**
	 * compares two objects by id.
	 */
	[[nodiscard]] bool operator== (SpaceObject const& other) const;
};

// doc strings at the friends function
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
