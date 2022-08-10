//
// PurpurTentakel
// 10.08.22
//

#include "Galaxy.h"

Galaxy::Galaxy(double x, double y, size_t planetCount, std::vector<std::unique_ptr<Player>> const& initialPlayer)
	: m_dimensions(x, y), m_planetCount(planetCount) {
	GeneratePlanets(initialPlayer);
	}

void Galaxy::GeneratePlanets(std::vector<std::unique_ptr<Player>> const& initialPlayer) {
	
}
