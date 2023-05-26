//
// PurpurTentakel
// 25.05.23
//

#include "HGalaxy.h"
#include "Fleet.h"
#include "SpaceObject.h"

std::pair<bool, SpaceObject_ty> TryGetTarget(
	Fleet const* fleet, SpaceObject_ty const& target) {

	if (target->IsFleet()) {
		if (target->GetID() == fleet->GetID()) {
			return { false, nullptr };
		}
		Fleet const* n_target = dynamic_cast<Fleet const*>(target.get());
		return TryGetTarget(fleet, n_target->GetTarget());
	}

	return { true, target };
}
