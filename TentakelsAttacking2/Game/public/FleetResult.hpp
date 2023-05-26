//
// Purpur Tentakel
// 23.05.2023
//

#include <memory>
class SpaceObject;

struct FleetResult final {
	SpaceObject_ty origin;
	Fleet_ty fleet;
	SpaceObject_ty destination;
	bool valid;
};
