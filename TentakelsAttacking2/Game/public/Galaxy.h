//
// PurpurTentakel
// 08.11.22
//

#pragma once
#include "Planet.h"
#include "SpaceObject.h"
#include "Vec2.hpp"
#include <vector>
#include <memory>

struct AppContext;

class Galaxy {
private:
	bool m_validGalaxy = true;
	std::vector<std::shared_ptr<SpaceObject>> m_objects;
	std::vector<std::shared_ptr<Planet>> m_planets;
	// m_fleets
	// m_targetPoints

	Vec2<size_t> m_size;

	[[nodiscard]] unsigned int GetNextID() const;
	void InitialzePlanets(int planetCount, std::vector<std::shared_ptr<Player>> players);
	[[nodiscard]] bool IsValidNewPlanet(std::shared_ptr<Planet> newPlanet, AppContext const& appContext) const;

public:
	Galaxy(Vec2<size_t> size, int planetCount, std::vector<std::shared_ptr<Player>> players);

	[[nodiscard]] bool IsValidGalaxy() const;
};