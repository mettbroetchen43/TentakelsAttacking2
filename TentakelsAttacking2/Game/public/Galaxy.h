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
	void InitialzePlanets(size_t planetCount, std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> neutralPlayer);
	[[nodiscard]] int GenerateHomePlanets(std::vector<std::shared_ptr<Player>> players);
	void GenerateOtherPlanets(size_t PlanetCount, int currentPlanet, std::shared_ptr<Player> player);
	[[nodiscard]] bool IsValidNewPlanet(std::shared_ptr<Planet> newPlanet, AppContext const& appContext) const;

public:
	Galaxy(Vec2<size_t> size, size_t planetCount, std::vector<std::shared_ptr<Player>> players,
		std::shared_ptr<Player> neutralPlayer);
	Galaxy(Galaxy const&);

	[[nodiscard]] bool IsValidGalaxy() const;

	[[nodiscard]] Vec2<size_t> GetSize() const;
	[[nodiscard]] std::vector<std::shared_ptr<Planet>> const GetPlanets() const;
};