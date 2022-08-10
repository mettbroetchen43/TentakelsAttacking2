//
// PurpurTentakel
// 08.08.22
//

#include "SpaceObject.h"

SpaceObject::SpaceObject(int id, double x, double y,int ships, std::weak_ptr<Player> player)
	: m_id(id), m_position(x,y),m_ships(ships), player(player) { }

Vec2<double> SpaceObject::GetPosition() const {
	return m_position;
}

int SpaceObject::GetId() const {
	return m_id;
}

void operator+=(SpaceObject& lhs, int ships) {
	lhs.m_ships += ships;
}

void operator-=(SpaceObject& lhs, int ships) {
	lhs.m_ships -= ships;
}

bool operator==(SpaceObject const& lhs, SpaceObject const& rhs) {
	return lhs.m_id == rhs.m_id;
}
