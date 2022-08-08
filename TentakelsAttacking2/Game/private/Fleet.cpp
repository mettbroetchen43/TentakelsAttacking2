//
// PurpurTentakel
// 08.08.22
//

#include "Fleet.h"

Fleet::Fleet(double x, double y, int ships, int index, Player const* player, GroupTarget& target)
	: SpaceObject(x, y), m_ships(ships), m_index(index), m_player(player), m_target(std::make_shared<GroupTarget*>(target)) { }

void Fleet::PreUpdate(GameManager const& gameManager) {
	Move();
}

void Fleet::operator+=(int ships) {
	m_ships += ships;
}
void Fleet::operator-=(int ships) {
	m_ships -= ships;
}
bool Fleet::operator==(Fleet const& other) {
	m_index == other.m_index;
}
