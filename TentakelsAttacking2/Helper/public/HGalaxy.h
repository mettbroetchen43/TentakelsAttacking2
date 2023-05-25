//
// PurpurTentakel
// 25.05.23
//

#pragma once
#include <utility>
#include <memory>

class Fleet;
class SpaceObject; 

[[nodiscard]] std::pair<bool, std::shared_ptr<SpaceObject>> TryGetTarget(
	std::shared_ptr<Fleet> const& fleet, std::shared_ptr<SpaceObject> const& target);
