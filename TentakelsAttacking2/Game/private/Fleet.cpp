//
// PurpurTentakel
// 08.08.22
//

#include "Fleet.h"
#include "Galaxy.h"
#include <memory>

Fleet::Fleet(int id, double x, double y, int ships, std::weak_ptr<Player> player, GroupTarget& target)
	: SpaceObject(id,x, y, ships, player), m_target(std::make_shared<GroupTarget>(target)) { }

void Fleet::Move(Galaxy const& galaxy) {

}

void Fleet::PreUpdate(Galaxy const& galaxy) {
	Move(galaxy);
}
void Fleet::Update(Galaxy const& galaxy) {

}
void Fleet::PostUpdate(Galaxy const& galaxy) {

}

std::string Fleet::ToString() const {
	return "Fleet // " + std::to_string(m_id) + " // " + m_position.ToString();
}
