//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "Vec2.h"
#include "SpaceObject.h"
#include "GroupTarget.h"
#include "Fleet.h"
#include <vector>

class Galaxy {
private:
	Vec2<double> m_dimensions;
	size_t m_planetCount;
	std::vector<std::unique_ptr<SpaceObject>> m_spaceObjects;
	std::vector<std::weak_ptr<GroupTarget>> m_groupTargets;
public:
	Galaxy(double x, double y, size_t planetCount, std::vector<std::unique_ptr<Player>> const& initialPlayer);
	void GeneratePlanets(std::vector<std::unique_ptr<Player>> const& initialPlayer);
};