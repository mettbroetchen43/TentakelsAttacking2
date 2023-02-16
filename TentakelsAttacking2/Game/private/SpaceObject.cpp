//
// Purpur Tentakel
// 06.11.2022
//

#include "SpaceObject.h"
#include <cassert>

SpaceObject::SpaceObject(unsigned int ID, vec2pos position, std::shared_ptr<Player> player)
	: m_ID(ID), m_position(position), m_player(player) {}
SpaceObject::SpaceObject(unsigned int ID, vec2pos position, size_t ships, std::shared_ptr<Player> player)
	: m_ID(ID), m_position(position), m_player(player), m_ships(ships) {}

unsigned int SpaceObject::GetID() const {
	return m_ID;
}

void SpaceObject::SetPlayer(std::shared_ptr<Player> player) {
	m_player = player;
}
std::shared_ptr<Player> SpaceObject::GetPlayer() const {
	return m_player;
}

void SpaceObject::SetPos(vec2pos pos) {
	m_position = pos;
}
SpaceObject::vec2pos SpaceObject::GetPos() const {
	return m_position;
}

size_t SpaceObject::GetShipCount() const {
	return m_ships;
}

bool SpaceObject::IsPlanet() const {

	return false;
}
bool SpaceObject::IsFleet() const {

	return false;
}
bool SpaceObject::IsTargetPoint() const {

	return false;
}

SpaceObject& SpaceObject::operator+=(size_t ships) {
	m_ships += ships;
	return *this;
}
SpaceObject& SpaceObject::operator+=(SpaceObject const& object) {
	m_ships += object.m_ships;
	return *this;
}
SpaceObject& SpaceObject::operator-=(size_t ships) {
	assert(m_ships >= ships);
	m_ships -= ships;
	return *this;
}
SpaceObject& SpaceObject::operator-=(SpaceObject const& object) {
	assert(m_ships >= object.m_ships);
	m_ships -= object.m_ships;
	return *this;
}
bool SpaceObject::operator==(SpaceObject const& other) const {
	return m_ID == other.m_ID;
}


// operator
size_t operator+(SpaceObject const& object, size_t ships) {
	return object.m_ships + ships;
}
size_t operator+(size_t ships, SpaceObject const& object) {
	return object + ships;
}
size_t operator+(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_ships + rhs.m_ships;
}

size_t operator-(SpaceObject const& object, size_t ships) {
	assert(object.m_ships >= ships);
	return object.m_ships - ships;
}
size_t operator-(size_t ships, SpaceObject const& object) {
	assert(ships >= object.m_ships);
	return ships - object.m_ships;
}
size_t operator-(SpaceObject const& lhs, SpaceObject const& rhs) {
	assert(lhs.m_ships >= rhs.m_ships);
	return lhs.m_ships - rhs.m_ships;
}

bool operator<(SpaceObject const& object, size_t ships) {
	return object.m_ships < ships;
}
bool operator<(size_t ships, SpaceObject const& object) {
	return ships < object.m_ships;
}
bool operator<(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_ships < rhs.m_ships;
}

bool operator<=(SpaceObject const& object, size_t ships) {
	return !(object > ships);
}
bool operator<=(size_t ships, SpaceObject const& object) {
	return !(ships > object);
}
bool operator<=(SpaceObject const& lhs, SpaceObject const& rhs) {
	return !(lhs > rhs);
}

bool operator>(SpaceObject const& object, size_t ships) {
	return object.m_ships > ships;
}
bool operator>(size_t ships, SpaceObject const& object) {
	return ships > object.m_ships;
}
bool operator>(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_ships > rhs.m_ships;
}

bool operator>=(SpaceObject const& object, size_t ships) {
	return !(object < ships);
}
bool operator>=(size_t ships, SpaceObject const& object) {
	return !(ships < object);
}
bool operator>=(SpaceObject const& lhs, SpaceObject const& rhs) {
	return !(lhs < rhs);
}
