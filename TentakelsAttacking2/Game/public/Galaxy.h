//
// PurpurTentakel
// 08.11.22
//

#pragma once
#include "Planet.h"
#include "TargetPoint.h"
#include "Fleet.h"
#include "GenerelEvents.hpp"
#include "Vec2.hpp"
#include <vector>
#include <memory>

struct AppContext;
struct FleetResult;

/**
 * contains objects witch include planet, fleets, target points
 * generates itself.
 */
class Galaxy final {
private:
	bool m_validGalaxy{ true }; ///< specifies if the generation in valid and the galaxy is able to use
	std::vector<SpaceObject_ty> m_objects; ///< contains all space object for updating 
	std::vector<std::shared_ptr<Planet>> m_planets; ///< contains all planets 
	std::vector<Fleet_ty> m_fleets; ///< contains all fleets
	std::vector<std::shared_ptr<TargetPoint>> m_targetPoints; ///< contains all target points

	Vec2<int> m_size; ///< contains the size of the galaxy

	/**
	 * returns the next free ID for an Space object that is the nearest to 0.
	 */
	[[nodiscard]] unsigned int GetNextID() const;

	// Planet
	/**
	 * coordinates the generation of all planets.
	 */
	void InitializePlanets(size_t planetCount, std::vector<Player_ty> players, Player_ty neutralPlayer);
	/**
	 * generation one home planet for every player.
	 * returns the planet count for generating the other planets.
	 */
	[[nodiscard]] int GenerateHomePlanets(std::vector<Player_ty> players);
	/**
	 * generation all other planet until the planet count is reached.
	 */
	void GenerateOtherPlanets(size_t PlanetCount, int currentPlanet, Player_ty player);
	/**
	 * validates if the new planet has a valid position.
	 * mainly if the distance to every other planet is big enough.
	 * returns a bool.
	 */
	[[nodiscard]] bool IsValidNewPlanet(std::shared_ptr<Planet> newPlanet, AppContext_ty_c appContext) const;

	// Fleet
	/**
	 * checks if the provided ID is a valid Feet.
	 */
	[[nodiscard]] bool IsValidFleet(unsigned int const ID) const;
	/**
	 * returns a fleet by ID.
	 * throws an runtime error if no Fleet exists for that ID.
	 */
	[[nodiscard]] Fleet_ty GetFleetByID(unsigned int const ID) const;
	/**
	 * returns a fleet if existing.
	 * returns a nullptr if not.
	 */
	[[nodiscard]] Fleet_ty TryGetExistingFleetByOriginAndDestination(
		SpaceObject_ty origin, SpaceObject_ty destination) const;

	/**
	 * validates the data from the UI if the instruction is for a planet.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] FleetResult AddFleetFromPlanet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);
	/**
	 * validates the data from the UI if the instruction is for a fleet.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] FleetResult AddFleetFromFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);
	/**
	 * validates the data from the UI if the instruction is for a target point.
	 * generates Popups if needed.
	 * add new fleet if valid.
	 */
	[[nodiscard]] FleetResult AddFleetFromTargetPoint(SendFleetInstructionEvent const* event, Player_ty currentPlayer);


	// Target Point
	/**
	 * checks if the provided ID is a target point.
	 */
	[[nodiscard]] bool IsValidTargetPoint(unsigned int const ID) const;
	/**
	 * returns the target point of the provided ID.
	 * throws an runtime error if no target point exists.
	 */
	[[nodiscard]] std::shared_ptr<TargetPoint> GetTargetPointByID(unsigned int const ID) const;

	/**
	 * returns a existing destination er generate a TargetPoint as destination.
	 */
	[[nodiscard]] SpaceObject_ty GetOrGenerateDestination(unsigned int ID,
		int X, int Y, Player_ty currentPlayer);

public:
	/**
	 * generates all planets.
	 * IsValid should be called after construction because there is no guaranty,
	 * that the	generation is valid.
	 */
	Galaxy(Vec2<int> size, size_t planetCount, std::vector<Player_ty> players,
		Player_ty neutralPlayer);
	/**
	 * makes a exact copy of a galaxy
	 */
	Galaxy(Galaxy const&);

	/**
	 * return if the galaxy is valid.
	 * if its not valid I really to not use this galaxy.
	 * this galaxy will not be complete then.
	 * you should generate a new one.
	 */
	[[nodiscard]] bool IsValid() const;

	/**
	 * returns true if the provided ID is existing in this galaxy.
	 */
	[[nodiscard]] bool IsValidSpaceObjectID(unsigned int ID) const;

	/**
	 * returns the size of the galaxy.
	 */
	[[nodiscard]] Vec2<int> GetSize() const;
	/**
	 * returns the planets of the galaxy.
	 */
	[[nodiscard]] std::vector<std::shared_ptr<Planet>> const GetPlanets() const;
	/**
	 * returns the fleets of the galaxy.
	 */
	[[nodiscard]] std::vector<Fleet_ty> const GetFleets() const;
	/**
	 * returns the target points of the galaxy.
	 */
	[[nodiscard]] std::vector<std::shared_ptr<TargetPoint>> const GetTargetPoints() const;
	/**
	 * returns a specific planet by ID.
	 */
	[[nodiscard]] std::shared_ptr<Planet> const GetPlanetByID(unsigned int ID) const;
	/**
	 * returns a SpaceObject with the provided ID.
	 * returns nullptr if there is no SpaceObject.
	 */
	[[nodiscard]] SpaceObject_ty const GetSpaceObjectByID(unsigned int ID) const;
	/**
	 * returns if the new position is a valid position.
	 */
	[[nodiscard]] bool IsValidPosition(Vec2<int>const& position) const;
	/**
	 * adds a new fleet to the galaxy for the provided player.
	 */
	[[nodiscard]] FleetResult AddFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer);
	/**
	 * filters the galaxy for relevant data for the provided player.
	 */
	void FilterByPlayer(unsigned int currentPlayerID);
	/**
	 * handles the changes of the FleetResult.
	 */
	void HandleFleetResult(FleetResult const& fleetResult);
	/**
	 * updates the Galaxy.
	 */
	void Update();
};
