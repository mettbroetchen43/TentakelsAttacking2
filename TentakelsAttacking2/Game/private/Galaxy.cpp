//
// PurpurTentakel
// 08.11.22
//

#include "Galaxy.h"
#include "AppContext.h"
#include "Player.h"
#include "HRandom.h"
#include "UIEvents.hpp"
#include "HPrint.h"
#include "GalaxyManager.h"
#include <stdexcept>

// help Lambdas
static auto popup = [](std::string const& text) {
	ShowMessagePopUpEvent const popupEvent{
		"Invalid Input",
		text,
		[]() {}
	};
	AppContext::GetInstance().eventManager.InvokeEvent(popupEvent);
};
static auto message = [](std::string& messageText, std::string const& first, std::string const& second) {
	if (messageText.size() <= 0) { messageText = first; return; }

	messageText += ", " + second;
};

unsigned int Galaxy::GetNextID() const {

	if (m_objects.empty()) { return 1; }

	unsigned int nextID{ 1 };
	while (true) {
		bool freeID{ true };
		for (auto& o : m_objects) {
			if (nextID == o->GetID()) {
				freeID = false;
				break;
			}
		}

		if (freeID) { return nextID; }

		++nextID;
	}
}

void Galaxy::InitializePlanets(size_t planetCount,
	std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> neutralPlayer) {

	int const currentPlanet{ GenerateHomePlanets(players) };
	if (m_validGalaxy) {
		GenerateOtherPlanets(planetCount, currentPlanet, neutralPlayer);
	}
}
int Galaxy::GenerateHomePlanets(std::vector<std::shared_ptr<Player>> players) {

	Random& random{ Random::GetInstance() };
	AppContext const& appContext{ AppContext::GetInstance() };
	int currentPlanet{ 1 };



	for (auto& p : players) {
		int counter{ 0 };
		while (true) {
			Vec2<int> const newPosition{
			   static_cast<int>(random.random(m_size.x)),
			   static_cast<int>(random.random(m_size.y))
			};

			auto const newPlanet = std::make_shared<Planet>(
				GetNextID(),
				newPosition,
				p,
				true,
				currentPlanet
			);
			newPlanet->SetDiscovered(true);

			if (IsValidNewPlanet(newPlanet, appContext)) {
				m_objects.push_back(newPlanet);
				m_planets.push_back(newPlanet);
				++currentPlanet;
				break;
			}

			++counter;

			if (counter > 10) {
				m_validGalaxy = false;
				return 0;
			}
		}
	}

	return currentPlanet;
}
void Galaxy::GenerateOtherPlanets(size_t planetCount, int currentPlanet,
	std::shared_ptr<Player> player) {

	AppContext const& appContext{ AppContext::GetInstance() };
	Random& random{ Random::GetInstance() };


	for (; currentPlanet <= planetCount; ++currentPlanet) {
		int counter{ 0 };
		while (true) {
			Vec2<int> const newPosition{
				static_cast<int>(random.random(m_size.x)),
				static_cast<int>(random.random(m_size.y))
			};

			auto const newPlanet = std::make_shared<Planet>(
				GetNextID(),
				newPosition,
				player,
				false,
				currentPlanet
			);

			if (IsValidNewPlanet(newPlanet, appContext)) {
				m_objects.push_back(newPlanet);
				m_planets.push_back(newPlanet);
				break;
			}

			++counter;

			if (counter > 10) {
				m_validGalaxy = false;
				return;
			}
		}
	}
}

bool Galaxy::IsValidNewPlanet(std::shared_ptr<Planet> newPlanet,
	AppContext const& appContext) const {
	bool validPlanet{ true };

	// works because Home Planets are generated first.
	float const factor = newPlanet->IsHomePlanet()
		? appContext.constants.planet.homeworldSpacing
		: appContext.constants.planet.globalSpacing;
	double const spacing{ m_size.Length() * factor };

	for (auto& p : m_planets) {
		double const currentSpacing{ (p->GetPos() - newPlanet->GetPos()).Length() };
		if (currentSpacing < spacing) {
			validPlanet = false;
			break;
		}
	}

	return validPlanet;
}

// Fleet
bool Galaxy::IsValidFleet(unsigned int const ID) const {
	
	for (auto const& f : m_fleets) {
		if (f->GetID() == ID) {
			return true;
		}
	}
	return false;
}
std::shared_ptr<Fleet> Galaxy::GetFleetByID(unsigned int const ID) const {
	for (auto const& f : m_fleets) {
		if (f->GetID() == ID) {
			return f;
		}
	}

	throw std::runtime_error("no fleet with this ID: " + std::to_string(ID));
}
[[nodiscard]] std::shared_ptr<Fleet> Galaxy::TryGetExistingFleetByOriginAndDestination(
	std::shared_ptr<SpaceObject> origin, std::shared_ptr<SpaceObject> destination) const {

	for (auto const& f : m_fleets) {
		if (f->GetPos() == origin->GetPos()) {
			if (f->GetTarget()->GetID() == destination->GetID()) {
				return f;
			}
		}
	}

	return nullptr;
}

bool Galaxy::AddFleetFromPlanet(SendFleetInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {
	// check origin id
	if (event->GetOrigin() > m_planets.size()) {
		popup("input for planet in origin to high");
		return false;
	}

	// check origin
	auto const originPlanet{ GetPlanetByID(static_cast<unsigned int>(event->GetOrigin())) };
	if (originPlanet->GetPlayer() != currentPlayer) {
		popup("the chosen origin isn't your Planet.");
		return false;
	}
	if (originPlanet->GetShipCount() < event->GetShipCount()) {
		popup("not enough ships on planet " + std::to_string(event->GetOrigin()));
		return false;
	}

	// get destination
	auto const destination = GetOrGenerateDestination(
		event->GetDestination(),
		static_cast<int>(event->GetDestinationX()),
		static_cast<int>(event->GetDestinationY()),
		currentPlayer
	);

	if (destination->IsPlanet()) {
		if (destination->GetID() == originPlanet->GetID()) {
			popup("origin planet and destination planet is the same planet");
			return false;
		}
	}
	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return false;
	}
	if (auto const fleet = TryGetExistingFleetByOriginAndDestination(originPlanet, destination)) {
		*originPlanet -= event->GetShipCount();
		*fleet        += event->GetShipCount();
		m_galaxyManager->m_currentGalaxy->MoveShips(
			originPlanet->GetID(),
			fleet->GetID(),
			event->GetShipCount()
		);

		return true;
	}

	// create fleet
	auto const fleet = std::make_shared<Fleet>(
		GetNextID(),
		originPlanet->GetPos(),
		event->GetShipCount(),
		currentPlayer,
		destination
	);

	m_objects.push_back(fleet);
	m_fleets.push_back(fleet);
	m_galaxyManager->m_currentGalaxy->AddSpaceObjectDirectly(fleet);

	// remove fleet ships from origin planet
	*originPlanet -= *fleet;
	m_galaxyManager->m_currentGalaxy->SubstractShips(
		originPlanet->GetID(),
		fleet->GetShipCount()
	);

	return true;
}
bool Galaxy::AddFleetFromFleet(SendFleetInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {
	// check if origin ID is existing
	if (not IsValidFleet(event->GetOrigin())) {
		popup("Fleet with ID " + std::to_string(event->GetOrigin()) + " is not existing");
		return false;
	}

	// check origin
	auto const& origin{ GetFleetByID(event->GetOrigin()) };
	if (origin->GetPlayer() != currentPlayer) {
		popup("the chosen origin isn't your fleet");
		return false;
	}
	if (origin->GetShipCount() < event->GetShipCount()) {
		popup("not enough ships in fleet " + std::to_string(event->GetOrigin()));
		return false;
	}

	// get destination
	auto const destination { GetOrGenerateDestination(
		event->GetDestination(),
		event->GetDestinationX(),
		event->GetDestinationY(),
		currentPlayer
	) };

	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return false;
	}

	if (destination->GetPos() == origin->GetPos()) {
		*origin      -= event->GetShipCount();
		*destination += event->GetShipCount();
		m_galaxyManager->m_currentGalaxy->MoveShips(
			origin->GetID(),
			destination->GetID(),
			event->GetShipCount()
		);
		return true;
	}
	if (auto const fleet = TryGetExistingFleetByOriginAndDestination(origin, destination)) {
		*origin -= event->GetShipCount();
		*fleet  += event->GetShipCount();
		m_galaxyManager->m_currentGalaxy->MoveShips(
			origin->GetID(),
			destination->GetID(),
			event->GetShipCount()
		);
		return true;
	}

	// create fleet
	auto const fleet = std::make_shared<Fleet>(
		GetNextID(),
		origin->GetPos(),
		event->GetShipCount(),
		currentPlayer,
		destination
	);

	m_objects.push_back(fleet);
	m_fleets.push_back(fleet);
	m_galaxyManager->m_currentGalaxy->AddSpaceObjectDirectly(fleet);

	// remove fleet ships from origin planet
	*origin -= *fleet;
	m_galaxyManager->m_currentGalaxy->SubstractShips(origin->GetID(), fleet->GetShipCount());

	return true;
}
bool Galaxy::AddFleetFromTargetPoint(SendFleetInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {
	// check if origin ID is existing
	if (not IsValidTargetPoint(event->GetOrigin())) {
		popup("no target point with ID " + std::to_string(event->GetOrigin()) + " existing");
		return false;
	}
	
	// check origin
	auto const& origin{ GetTargetPointByID(event->GetOrigin()) };
	if (origin->GetPlayer() != currentPlayer) {
		popup("the chosen origin isn't your target point");
		return false;
	}
	if (origin->GetShipCount() < event->GetShipCount()) {
		popup("not enough ships at target point " + std::to_string(event->GetOrigin()));
		return false;
	}

	// get destination
	auto const destination { GetOrGenerateDestination(
		event->GetDestination(),
		event->GetDestinationX(),
		event->GetDestinationY(),
		currentPlayer
	) };

	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return false;
	}

	if (origin->GetPos() == destination->GetPos()) {
		*origin      -= event->GetShipCount();
		*destination += event->GetShipCount();
		m_galaxyManager->m_currentGalaxy->MoveShips(
			origin->GetID(),
			destination->GetID(),
			event->GetShipCount()
		);
		return true;
	}
	if (auto const& fleet = TryGetExistingFleetByOriginAndDestination(origin, destination)) {
		*origin      -= event->GetShipCount();
		*destination += event->GetShipCount();
		m_galaxyManager->m_currentGalaxy->MoveShips(
			origin->GetID(),
			destination->GetID(),
			event->GetShipCount()
		);
		return true;
	}

	// get fleet
	auto const fleet = std::make_shared<Fleet>(
		GetNextID(),
		origin->GetPos(),
		event->GetShipCount(),
		currentPlayer,
		destination
	);

	m_objects.push_back(fleet);
	m_fleets.push_back(fleet);
	m_galaxyManager->m_currentGalaxy->AddSpaceObjectDirectly(fleet);

	// manage ships
	*origin -= *fleet;
	m_galaxyManager->m_currentGalaxy->SubstractShips(origin->GetID(), fleet->GetShipCount());

	return false;
}

// Target Point
bool Galaxy::IsValidTargetPoint(unsigned int const ID) const {
	for (auto const& tp : m_targetPoints) {
		if (tp->GetID() == ID) {
			return true;
		}
	}
	return false;
}
std::shared_ptr<TargetPoint> Galaxy::GetTargetPointByID(unsigned int const ID) const {
	for (auto const& tp : m_targetPoints) {
		if (tp->GetID() == ID) {
			return tp;
		}
	}

	throw std::runtime_error("no Target Point with ID " + std::to_string(ID));
}

std::shared_ptr<SpaceObject> Galaxy::GetOrGenerateDestination(unsigned int ID,
	int X, int Y, std::shared_ptr<Player> currentPlayer) {

	for (auto& object : m_objects) {

		if (object->GetID() == ID) { return object; }

		auto const pos{ object->GetPos() };
		if (pos.x == X && pos.y == Y) {
			if (object->GetPlayer() == currentPlayer) {
				return object;
			}
		}
	}

	Vec2<int> const point{ X,Y };
	auto const targetPoint = std::make_shared<TargetPoint>(
		GetNextID(),
		point,
		currentPlayer
	);

	m_objects.push_back(targetPoint);
	m_targetPoints.push_back(targetPoint);
	m_galaxyManager->m_currentGalaxy->AddSpaceObjectDirectly(targetPoint);

	return targetPoint;
}



Galaxy::Galaxy(Vec2<int> size, size_t planetCount,
	std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> neutralPlayer, GalaxyManager* galaxyManager)
	: m_size{ size }, m_galaxyManager{ galaxyManager }  {

	InitializePlanets(planetCount, players, neutralPlayer);
}
Galaxy::Galaxy(Galaxy const& old)
	: m_validGalaxy{ old.m_validGalaxy }, m_size{ old.m_size }, m_galaxyManager{ old.m_galaxyManager } {

	for (auto o : old.m_objects) {
		if (o->IsFleet()) {
			auto const object = std::make_shared<Fleet>(*std::static_pointer_cast<Fleet>(o));
			m_objects.push_back(object);
			m_fleets.push_back(object);
		}
		else if (o->IsPlanet()) {
			auto const object = std::make_shared<Planet>(*std::static_pointer_cast<Planet>(o));
			m_objects.push_back(object);
			m_planets.push_back(object);
		}
		else if (o->IsTargetPoint()) {
			auto const object = std::make_shared<TargetPoint>(*std::static_pointer_cast<TargetPoint>(o));
			m_objects.push_back(object);
			m_targetPoints.push_back(object);
		}
		else {
			throw std::invalid_argument("invalid Space Object");
		}
	}
}

bool Galaxy::IsValid() const {
	return m_validGalaxy;
}

bool Galaxy::IsValidSpaceObjectID(unsigned int ID) const {

	for (auto const& object : m_objects) {
		if (object->GetID() == ID) {
			return true;
		}
	}

	return false;
}

Vec2<int> Galaxy::GetSize() const {
	return m_size;
}
std::vector<std::shared_ptr<Planet>> const Galaxy::GetPlanets() const {
	return m_planets;
}

std::vector<std::shared_ptr<Fleet>> const Galaxy::GetFleets() const {
	return m_fleets;
}

std::vector<std::shared_ptr<TargetPoint>> const Galaxy::GetTargetPoints() const {
	return m_targetPoints;
}

std::shared_ptr<Planet> const Galaxy::GetPlanetByID(unsigned int ID) const {
	for (auto const& planet : m_planets) {
		if (planet->GetID() == ID) {
			return planet;
		}
	}

	throw std::runtime_error("no planet with this ID: " + std::to_string(ID));
}

std::shared_ptr<SpaceObject> const Galaxy::GetSpaceObjectByID(unsigned int ID) const {

	for (auto const& object : m_objects) {
		if (object->GetID() == ID) {
			return object;
		}
	}

	throw std::runtime_error("no space object with ID " + std::to_string(ID));
}

bool Galaxy::AddFleet(SendFleetInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {

	// valid ID?
	if (!IsValidSpaceObjectID(event->GetOrigin())) {
		popup("ID not existing as origin: " + std::to_string(event->GetOrigin()));
		return false;
	}
	if (!IsValidSpaceObjectID(event->GetDestination())) {

		bool const validCoordinates{
				(event->GetDestinationX() > 0
			and event->GetDestinationX() <= m_size.x)
			and (event->GetDestinationY() > 0
			and event->GetDestinationY() <= m_size.y)
		};
		bool const coordinateInput{
				event->GetDestinationX() > 0 
			and event->GetDestinationY() > 0
		};

		if (!validCoordinates && coordinateInput) {
			popup("destination coordinates outside of the map. X: "
				+ std::to_string(event->GetDestinationX())
				+ ", Y: "
				+ std::to_string(event->GetDestinationY())
			);
			return false;
		}
		else if (!coordinateInput) {
			popup("ID not existing as destination: " + std::to_string(event->GetDestination()));
			return false;
		}
	}

	// get origin and set new fleet
	auto const& origin{ GetSpaceObjectByID(event->GetOrigin()) };

	if (origin->IsPlanet()) {
		return AddFleetFromPlanet(event, currentPlayer);
	}
	if (origin->IsFleet()) {
		return AddFleetFromFleet(event, currentPlayer);
	}
	if (origin->IsTargetPoint()) {
		return AddFleetFromTargetPoint(event, currentPlayer);
	}

	popup("can't recognize provided origin: " + std::to_string(event->GetOrigin()));
	return false;
}

void Galaxy::FilterByPlayer(unsigned int currentPlayerID) {
	auto const newEnd{ std::remove_if(m_fleets.begin(), m_fleets.end(),
		[currentPlayerID](std::shared_ptr<Fleet> const& fleet) { return fleet->GetPlayer()->GetID() != currentPlayerID; }) };
	m_fleets.erase(newEnd, m_fleets.end());

	auto const newEnd2{ std::remove_if(m_objects.begin(), m_objects.end(),
		[currentPlayerID](std::shared_ptr<SpaceObject> const& object) { return object->IsFleet() and object->GetPlayer()->GetID() != currentPlayerID; }) };
	m_objects.erase(newEnd2, m_objects.end());

	auto const newEnd3{ std::remove_if(m_targetPoints.begin(), m_targetPoints.end(),
		[currentPlayerID](std::shared_ptr<TargetPoint> const& targetPoint) { return targetPoint->GetPlayer()->GetID() != currentPlayerID; }) };
	m_targetPoints.erase(newEnd3, m_targetPoints.end());

	auto const newEnd4{ std::remove_if(m_objects.begin(), m_objects.end(),
		[currentPlayerID](std::shared_ptr<SpaceObject> const& object) {return object->IsTargetPoint() and object->GetPlayer()->GetID() != currentPlayerID; } )};
	m_objects.erase(newEnd4, m_objects.end());
}

void Galaxy::MoveShips(unsigned int originID, unsigned int destinationID, size_t ships) {
	auto origin{ GetSpaceObjectByID(originID) };
	auto destination{ GetSpaceObjectByID(destinationID) };
	*origin -= ships;
	*destination += ships;
}
void Galaxy::SubstractShips(unsigned int spaceObjectID, size_t ships) {
	auto spaceObject{ GetSpaceObjectByID(spaceObjectID) };
	*spaceObject -= ships;
}

void Galaxy::AddSpaceObjectDirectly(std::shared_ptr<SpaceObject> object) {
	if (object->IsPlanet()) {
		auto const newObject = std::make_shared<Planet>(*std::static_pointer_cast<Planet>(object));
		m_objects.push_back(newObject);
		m_planets.push_back(newObject);
	}
	if (object->IsFleet()) {
		auto const newObject = std::make_shared<Fleet>(*std::static_pointer_cast<Fleet>(object));
		m_objects.push_back(newObject);
		m_fleets.push_back(newObject);
	}
	if (object->IsTargetPoint()) {
		auto const newObject = std::make_shared<TargetPoint>(*std::static_pointer_cast<TargetPoint>(object));
		m_objects.push_back(newObject);
		m_targetPoints.push_back(newObject);
	}
}

void Galaxy::Update() {
	for (auto& o : m_objects) {
		o->Update();
	}
}
