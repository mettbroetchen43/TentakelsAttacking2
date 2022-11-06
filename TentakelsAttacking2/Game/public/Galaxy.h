//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "Vec2.hpp"
#include "Fleet.h"
#include "Planet.h"
#include "GroupTarget.h"
#include <vector>
#include <iostream>

class Galaxy final {
private:
	Vec2<double> m_dimensions;
	size_t m_planetCount;
	std::vector<std::shared_ptr<Planet>> m_planets;
	std::vector<std::shared_ptr<Fleet>> m_fleets;
	std::vector<std::weak_ptr<SpaceObject>> m_spaceObjects;
	std::vector<std::weak_ptr<GroupTarget>> m_groupTargets;
public:
	Galaxy(double x, double y, size_t planetCount, std::vector<std::shared_ptr<Player>> const& initialPlayer);
	void GeneratePlanets(std::vector<std::shared_ptr<Player>> const& initialPlayer);
	Galaxy();

	void PreUpdate();
	void Update();
	void PostUpdate();
};