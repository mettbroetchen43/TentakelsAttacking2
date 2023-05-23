//
// PurpurTentakel
// 16.02.22
//

#include "Fleet.h"
#include "HPrint.h"

Fleet::Fleet(unsigned int ID, vec2pos position, std::shared_ptr<Player> player,
    std::shared_ptr<SpaceObject> target)
    : SpaceObject{ ID, position, player }, m_target{ target } { }

Fleet::Fleet(unsigned int ID, vec2pos position, size_t ships, std::shared_ptr<Player> player,
    std::shared_ptr<SpaceObject> target)
    : SpaceObject{ ID, position, ships, player }, m_target{ target } { }

bool Fleet::IsFleet() const {
    return true;
}

std::shared_ptr<SpaceObject> Fleet::GetTarget() const {
    return m_target;
}

void Fleet::Update() {
    Print("Update Fleet, Fleet should move", PrintType::DEBUG);
}