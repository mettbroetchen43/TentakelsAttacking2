//
// Purpur Tentakel
// 23.05.2023
//

#include <memory>
class SpaceObject;

struct FleetResult final {
	std::shared_ptr<SpaceObject> origin;
	std::shared_ptr<Fleet> fleet;
	std::shared_ptr<SpaceObject> destination;
	bool valid;
};
