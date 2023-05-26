//
// PurpurTentakel
// 25.05.23
//

#pragma once
#include <utility>
#include <memory>
#include <CLogicAlias.hpp>

class Fleet;

[[nodiscard]] std::pair<bool, SpaceObject_ty> TryGetTarget(
	Fleet const* fleet, SpaceObject_ty const& target);
