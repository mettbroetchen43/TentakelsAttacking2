//
// Purpur Tentakel
// 06.11.2022
//

#pragma once
#include <memory>
#include "Vec2.hpp"
#include <string>
#include <memory>
#include "LogicUpdate.hpp"

class Player;

/**
 * the basic space object, that every element in the galaxy is implementing.
 */
class SpaceObject /*: public LogicUpdate */ {
protected:
	using vec2pos = Vec2<int>; ///< the position type
	unsigned int m_ID; ///< contains the unique id
	size_t m_ships = 0; ///< contains the current ampunt of ships
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
	 * adds and returns the shipcount of an object and a number.
	 */
	friend size_t operator+ (SpaceObject const& object, size_t ships);
	/**
	 * adds and returns the shipcount of an object and a number.
	 */
	friend size_t operator+ (size_t ships, SpaceObject const& object);
	/**
	 * adds and returns two shipcounts.
	 */
	friend size_t operator+ (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * substracts and returns the shipcount of an object and a number.
	 */
	friend size_t operator- (SpaceObject const& object, size_t ships);
	/**
	 * substracts and returns the shipcount of an object and a number.
	 */
	friend size_t operator- (size_t ships, SpaceObject const& object);
	/**
	 * substracts and returns two shipcounts.
	 */
	friend size_t operator- (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the shipcount is smaller than the number. 
	 */
	friend bool operator< (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is smaller than the shipcount.
	 */
	friend bool operator< (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs shipcount smaller than the rhs shipcount.
	 */
	friend bool operator< (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the shipcount is smaller than or eqal to the number.
	 */
	friend bool operator<= (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is smaller than or qual to the shipcount.
	 */
	friend bool operator<= (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs shipcount smaller than or qual to the rhs shipcount.
	 */
	friend bool operator<= (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the shipcount is greater than the number.
	 */
	friend bool operator> (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is greater than the shipcount.
	 */
	friend bool operator> (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs shipcount greater than the rhs shipcount.
	 */
	friend bool operator> (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * compares if the shipcount is greater than or eqal to the number.
	 */
	friend bool operator>= (SpaceObject const& object, size_t ships);
	/**
	 * compares if the number is greater than or qual to the shipcount.
	 */
	friend bool operator>= (size_t ships, SpaceObject const& object);
	/**
	 * compares if the number is lhs shipcount freater than or qual to the rhs shipcount.
	 */
	friend bool operator>= (SpaceObject const& lhs, SpaceObject const& rhs);

	/**
	 * add an ammount of ships to the shipcount.
	 */
	SpaceObject& operator+=(size_t ships);
	/**
	 * add an other shipcount to the shipcount.
	 */
	SpaceObject& operator+=(SpaceObject const& object);

	/**
	 * substract an ammount of ships to the shipcount.
	 */
	SpaceObject& operator-=(size_t ships);
	/**
	 * substract an other shipcount to the shipcount.
	 */
	SpaceObject& operator-=(SpaceObject const& object);

	/**
	 * compares two objects by id.
	 */
	[[nodiscard]] bool operator== (SpaceObject const& other) const;
};

// doc strings at the frends function
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
