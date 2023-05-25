//
// PurpurTentakel
// 25.05.23
//

#include "HGalaxy.h"
#include "Fleet.h"
#include "SpaceObject.h"

std::pair<bool, std::shared_ptr<SpaceObject>> TryGetTarget(
	Fleet const* fleet, std::shared_ptr<SpaceObject>const& target) {

	if (target->IsFleet()) {
		if (target->GetID() == fleet->GetID()) {
			return { false, nullptr };
		}
		Fleet const* n_target = dynamic_cast<Fleet const*>(target.get());
		return TryGetTarget(fleet, n_target->GetTarget());
	}

	return { true, target };
}
