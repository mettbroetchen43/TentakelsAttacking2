//
// PurpurTentakel
// 16.02.22
//

#include "Fleet.h"
#include "HPrint.h"
#include "Galaxy.h"
#include "HGalaxy.h"
#include "AppContext.h"
#include <cmath>

Fleet::Fleet(unsigned int ID, vec2pos position, Player_ty player,
    SpaceObject_ty target)
    : SpaceObject{ ID, position, player }, m_target{ target } { }

Fleet::Fleet(unsigned int ID, vec2pos position, size_t ships, Player_ty player,
    SpaceObject_ty target)
    : SpaceObject{ ID, position, ships, player }, m_target{ target } { }

bool Fleet::IsFleet() const {
    return true;
}

SpaceObject_ty Fleet::GetTarget() const {
    return m_target;
}

void Fleet::Update(Galaxy_ty_raw galaxy) {

    auto [valid, target] { TryGetTarget(this, m_target) };
    if (not valid) { target = m_target; };

    int speed = AppContext::GetInstance().constants.fleet.currentFleetSpeed;
    float constexpr dl = 0.001f;
    int const x1{ m_position.x };
    int const y1{ m_position.y };
    int const x2{ target->GetPos().x };
    int const y2{ target->GetPos().y };
    int const dx = x2 - x1;
    int const dy = y2 - y1;
    std::vector<Vec2<int>> route;

    auto addPosition = [&](Vec2<int> const& new_) {
        for (auto const& v : route) {
            if (v == new_) {
                return;
            }
        }
        route.push_back(new_);
    };
    auto generatePosition = [&]() {
        for (float l = 0.0f; l < 1.0f; l += dl) {
            Vec2<int> newPos{
                x1 + static_cast<int>(std::floor(dx * l + 0.5f)),
                y1 + static_cast<int>(std::floor(dy * l + 0.5f))
            };
            addPosition(newPos);
        }
    };
    auto setSpeed = [&](Vec2<int> const& old, Vec2<int> const& new_) {
        Vec2<int> offset = Abs<int>(old - new_);
        speed -= offset.x;
        speed -= offset.y;
    };
    auto filterPosition = [&]() -> Vec2<int> {
        Vec2<int> old = m_position;
        Vec2<int> new_ = target->GetPos();
        for (int i = 1; i < route.size(); ++i) {
            old = route.at(i - 1);
            new_ = route.at(i);
            if (galaxy->IsValidPosition(new_)) {
                setSpeed(old, new_);
            }

            if (speed <= 0) {
                break;
            }
        }
        return new_;
    };

    generatePosition();
    m_position = filterPosition();
}