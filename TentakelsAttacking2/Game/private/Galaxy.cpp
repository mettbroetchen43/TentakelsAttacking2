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
#include "FleetResult.hpp"
#include "HGalaxy.h"
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
	std::vector<Player_ty> players, Player_ty neutralPlayer) {

	int const currentPlanet{ GenerateHomePlanets(players) };
	if (m_validGalaxy) {
		GenerateOtherPlanets(planetCount, currentPlanet, neutralPlayer);
	}
}
int Galaxy::GenerateHomePlanets(std::vector<Player_ty> players) {

	Random& random{ Random::GetInstance() };
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	int currentPlanet{ 1 };



	for (auto& p : players) {
		int counter{ 0 };
		while (true) {
			vec2pos_ty_c newPosition{
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
	Player_ty player) {

	AppContext_ty_c appContext{ AppContext::GetInstance() };
	Random& random{ Random::GetInstance() };


	for (; currentPlanet <= planetCount; ++currentPlanet) {
		int counter{ 0 };
		while (true) {
			vec2pos_ty_c newPosition{
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

bool Galaxy::IsValidNewPlanet(Planet_ty newPlanet,
	AppContext_ty_c appContext) const {
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
Fleet_ty Galaxy::GetFleetByID(unsigned int const ID) const {
	for (auto const& f : m_fleets) {
		if (f->GetID() == ID) {
			return f;
		}
	}

	throw std::runtime_error("no fleet with this ID: " + std::to_string(ID));
}
[[nodiscard]] Fleet_ty Galaxy::TryGetExistingFleetByOriginAndDestination(
	SpaceObject_ty origin, SpaceObject_ty destination) const {

	for (auto const& f : m_fleets) {
		if (f->GetPos() == origin->GetPos()) {
			if (f->GetTarget()->GetID() == destination->GetID()) {
				return f;
			}
		}
	}

	return nullptr;
}

FleetResult Galaxy::AddFleetFromPlanet(SendFleetInstructionEvent const* event, Player_ty currentPlayer) {
	// check origin id
	if (event->GetOrigin() > m_planets.size()) {
		popup("input for planet in origin to high");
		return { nullptr, nullptr, nullptr, false };
	}

	// check origin
	auto const originPlanet{ GetPlanetByID(static_cast<unsigned int>(event->GetOrigin())) };
	if (originPlanet->GetPlayer() != currentPlayer) {
		popup("the chosen origin isn't your Planet.");
		return { nullptr, nullptr, nullptr, false };
	}
	if (originPlanet->GetShipCount() < event->GetShipCount()) {
		popup("not enough ships on planet " + std::to_string(event->GetOrigin()));
		return { nullptr, nullptr, nullptr, false };
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
			return { nullptr, nullptr, nullptr, false };
		}
	}
	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return { nullptr, nullptr, nullptr, false };
	}
	if (auto const fleet = TryGetExistingFleetByOriginAndDestination(originPlanet, destination)) {
		*originPlanet -= event->GetShipCount();
		*fleet += event->GetShipCount();
		return { originPlanet, fleet, nullptr, true };
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

	// remove fleet ships from origin planet
	*originPlanet -= *fleet;

	return { originPlanet, fleet, destination, true };
}
FleetResult Galaxy::AddFleetFromFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer) {
	// check if origin ID is existing
	if (not IsValidFleet(event->GetOrigin())) {
		popup("Fleet with ID " + std::to_string(event->GetOrigin()) + " is not existing");
		return { nullptr, nullptr, nullptr, false };
	}

	// check origin
	auto const& origin{ GetFleetByID(event->GetOrigin()) };
	if (origin->GetPlayer() != currentPlayer) {
		popup("the chosen origin isn't your fleet");
		return { nullptr, nullptr, nullptr, false };
	}
	if (origin->GetShipCount() < event->GetShipCount()) {
		popup("not enough ships in fleet " + std::to_string(event->GetOrigin()));
		return { nullptr, nullptr, nullptr, false };
	}

	// get destination
	auto const destination{ GetOrGenerateDestination(
		event->GetDestination(),
		event->GetDestinationX(),
		event->GetDestinationY(),
		currentPlayer
	) };

	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return { nullptr, nullptr, nullptr, false };
	}

	if (destination->GetPos() == origin->GetPos()) {
		*origin -= event->GetShipCount();
		*destination += event->GetShipCount();
		return { origin, nullptr, destination, true };
	}
	if (auto const fleet = TryGetExistingFleetByOriginAndDestination(origin, destination)) {
		*origin -= event->GetShipCount();
		*fleet += event->GetShipCount();
		return { origin, fleet, nullptr, true };
	}

	// create fleet
	auto const fleet = std::make_shared<Fleet>(
		GetNextID(),
		origin->GetPos(),
		event->GetShipCount(),
		currentPlayer,
		destination
	);

	if (destination->IsFleet()) {
		auto const result{ TryGetTarget(fleet.get(), fleet->GetTarget())};
		if (not result.first) { // not valid
			popup("this operation would produce a fleet circle");
			return { nullptr, nullptr, nullptr, false };
		}
	}

	m_objects.push_back(fleet);
	m_fleets.push_back(fleet);

	// remove fleet ships from origin planet
	*origin -= *fleet;

	return { origin, fleet, destination, true };
}
FleetResult Galaxy::AddFleetFromTargetPoint(SendFleetInstructionEvent const* event, Player_ty currentPlayer) {
	// check if origin ID is existing
	if (not IsValidTargetPoint(event->GetOrigin())) {
		popup("no target point with ID " + std::to_string(event->GetOrigin()) + " existing");
		return { nullptr, nullptr, nullptr, false };
	}

	// check origin
	auto const& origin{ GetTargetPointByID(event->GetOrigin()) };
	if (origin->GetPlayer() != currentPlayer) {
		popup("the chosen origin isn't your target point");
		return { nullptr, nullptr, nullptr, false };
	}
	if (origin->GetShipCount() < event->GetShipCount()) {
		popup("not enough ships at target point " + std::to_string(event->GetOrigin()));
		return { nullptr, nullptr, nullptr, false };
	}

	// get destination
	auto const destination{ GetOrGenerateDestination(
		event->GetDestination(),
		event->GetDestinationX(),
		event->GetDestinationY(),
		currentPlayer
	) };

	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return { nullptr, nullptr, nullptr, false };
	}

	if (origin->GetPos() == destination->GetPos()) {
		*origin -= event->GetShipCount();
		*destination += event->GetShipCount();
		return { origin, nullptr, destination, true };
	}
	if (auto const& fleet = TryGetExistingFleetByOriginAndDestination(origin, destination)) {
		*origin -= event->GetShipCount();
		*destination += event->GetShipCount();
		return { origin, nullptr, destination, true };
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

	// manage ships
	*origin -= *fleet;

	return { origin, fleet, destination, true };
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

SpaceObject_ty Galaxy::GetOrGenerateDestination(unsigned int ID,
	int X, int Y, Player_ty currentPlayer) {

	for (auto& object : m_objects) {

		if (object->GetID() == ID) { return object; }

		auto const pos{ object->GetPos() };
		if (pos.x == X && pos.y == Y) {
			if (object->GetPlayer() == currentPlayer) {
				return object;
			}
		}
	}

	vec2pos_ty_c point{ X,Y };
	auto const targetPoint = std::make_shared<TargetPoint>(
		GetNextID(),
		point,
		currentPlayer
	);

	m_objects.push_back(targetPoint);
	m_targetPoints.push_back(targetPoint);

	return targetPoint;
}



Galaxy::Galaxy(vec2pos_ty size, size_t planetCount,
	std::vector<Player_ty> players, Player_ty neutralPlayer)
	: m_size{ size } {

	InitializePlanets(planetCount, players, neutralPlayer);
}
Galaxy::Galaxy(Galaxy const& old)
	: m_validGalaxy{ old.m_validGalaxy }, m_size{ old.m_size } {

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

vec2pos_ty Galaxy::GetSize() const {
	return m_size;
}
std::vector<Planet_ty> const Galaxy::GetPlanets() const {
	return m_planets;
}

std::vector<Fleet_ty> const Galaxy::GetFleets() const {
	return m_fleets;
}

std::vector<std::shared_ptr<TargetPoint>> const Galaxy::GetTargetPoints() const {
	return m_targetPoints;
}

Planet_ty const Galaxy::GetPlanetByID(unsigned int ID) const {
	for (auto const& planet : m_planets) {
		if (planet->GetID() == ID) {
			return planet;
		}
	}

	throw std::runtime_error("no planet with this ID: " + std::to_string(ID));
}

SpaceObject_ty const Galaxy::GetSpaceObjectByID(unsigned int ID) const {

	for (auto const& object : m_objects) {
		if (object->GetID() == ID) {
			return object;
		}
	}

	return nullptr;
}

bool Galaxy::IsValidPosition(vec2pos_ty_ref_c position) const {
	for (auto const& p : m_planets) {
		if (p->GetPos() == position) {
			return false;
		}
	}
	return true;
}

FleetResult Galaxy::AddFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer) {

	// valid ID?
	if (!IsValidSpaceObjectID(event->GetOrigin())) {
		popup("ID not existing as origin: " + std::to_string(event->GetOrigin()));
		return { nullptr, nullptr, nullptr, false };
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
			return { nullptr, nullptr, nullptr, false };
		}
		else if (!coordinateInput) {
			popup("ID not existing as destination: " + std::to_string(event->GetDestination()));
			return { nullptr, nullptr, nullptr, false };
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
	return { nullptr, nullptr, nullptr, false };
}

void Galaxy::FilterByPlayer(unsigned int currentPlayerID) {
	auto const newEnd{ std::remove_if(m_fleets.begin(), m_fleets.end(),
		[currentPlayerID](Fleet_ty_c fleet) { return fleet->GetPlayer()->GetID() != currentPlayerID; }) };
	m_fleets.erase(newEnd, m_fleets.end());

	auto const newEnd2{ std::remove_if(m_objects.begin(), m_objects.end(),
		[currentPlayerID](SpaceObject_ty const& object) { return object->IsFleet() and object->GetPlayer()->GetID() != currentPlayerID; }) };
	m_objects.erase(newEnd2, m_objects.end());

	auto const newEnd3{ std::remove_if(m_targetPoints.begin(), m_targetPoints.end(),
		[currentPlayerID](std::shared_ptr<TargetPoint> const& targetPoint) { return targetPoint->GetPlayer()->GetID() != currentPlayerID; }) };
	m_targetPoints.erase(newEnd3, m_targetPoints.end());

	auto const newEnd4{ std::remove_if(m_objects.begin(), m_objects.end(),
		[currentPlayerID](SpaceObject_ty const& object) {return object->IsTargetPoint() and object->GetPlayer()->GetID() != currentPlayerID; }) };
	m_objects.erase(newEnd4, m_objects.end());
}

void Galaxy::HandleFleetResult(FleetResult const& fleetResult) {
	auto add = [this](SpaceObject_ty const& obj) {
		if (obj->IsPlanet()) {
			auto const* planet = dynamic_cast<Planet_ty_raw>(obj.get());
			auto newDest = std::make_shared<Planet>(
				planet->GetID(),
				planet->GetPos(),
				planet->GetPlayer(),
				planet->IsHomePlanet(),
				planet->GetPlanetNumber(),
				planet->GetShipCount()
			);
			this->m_objects.push_back(newDest);
			this->m_planets.push_back(newDest);

		}
		else if (obj->IsFleet()) {
			auto const* fleet = dynamic_cast<Fleet_ty_raw>(obj.get());
			auto newDest = std::make_shared<Fleet>(
				fleet->GetID(),
				fleet->GetPos(),
				fleet->GetShipCount(),
				fleet->GetPlayer(),
				fleet->GetTarget()
			);
			this->m_objects.push_back(newDest);
			this->m_fleets.push_back(newDest);
		}
		else if (obj->IsTargetPoint()) {
			auto const* t_p = dynamic_cast<TargetPoint const*>(obj.get());
			auto newDest = std::make_shared<TargetPoint>(
				t_p->GetID(),
				t_p->GetPos(),
				t_p->GetShipCount(),
				t_p->GetPlayer()
			);
			this->m_objects.push_back(newDest);
			this->m_targetPoints.push_back(newDest);
		}
	};
	auto handle = [this, add](SpaceObject_ty const& obj) {
		if (obj) {
			auto& my_obj{ this->GetSpaceObjectByID(obj->GetID()) };
			if (my_obj) {
				my_obj->SetShipCount(obj->GetShipCount());
			}
			else {
				add(obj);
			}
		}
	};

	handle(fleetResult.origin);
	handle(fleetResult.fleet);
	handle(fleetResult.destination);
}

void Galaxy::Update() {
	for (auto& o : m_objects) {
		o->Update(this);
	}
}
