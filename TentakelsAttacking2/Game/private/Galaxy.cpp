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
#include "HFleetResult.hpp"
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

	// check destination
	if (destination->GetPlayer() != currentPlayer and not destination->IsPlanet()) {
		popup("destination isn't yours");
		return { nullptr, nullptr, nullptr, false };
	}

	// shift ships directly
	if (destination->GetPos() == origin->GetPos()) {
		*origin -= event->GetShipCount();
		*destination += event->GetShipCount();
		return { origin, nullptr, destination, true };
	}
	if (auto const fleet{ TryGetExistingFleetByOriginAndDestination(origin, destination) }) {
		*origin -= event->GetShipCount();
		*fleet += event->GetShipCount();
		return { origin, fleet, nullptr, true };
	}

	// redirect fleet
	if (origin->GetShipCount() == event->GetShipCount()) {
		origin->SetTarget(destination);
		return { origin, nullptr, nullptr, true };
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
		auto const result{ TryGetTarget(fleet.get(), fleet->GetTarget()) };
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

std::vector<Fleet_ty> Galaxy::GetFleetsOfTarget(SpaceObject_ty object) const {
	std::vector<Fleet_ty> vec{ };

	for (auto const& fleet : m_fleets) {
		if (fleet->GetTarget()->GetID() == object->GetID()) {
			vec.push_back(fleet);
		}
	}

	return vec;
}

void Galaxy::DeleteFleet(std::vector<Fleet_ty> const& fleets) {
	auto const& containsFleet{ [fleets](Fleet_ty const& fleet) -> bool {
		for (auto const& fleet_r : fleets) {
			if (fleet->GetID() == fleet_r->GetID()) {
				return true;
			}
		}
		return false;
	} };
	auto const& containsObject{ [fleets](SpaceObject_ty const& object) -> bool {
		for (auto const& fleet : fleets) {
			if (object->GetID() == fleet->GetID()) {
				return true;
			}
		}
		return false;
	} };

	auto const newStart1{ std::remove_if(m_fleets.begin(), m_fleets.end(), containsFleet) };
	m_fleets.erase(newStart1, m_fleets.end());

	auto const newStart2{ std::remove_if(m_objects.begin(), m_objects.end(), containsObject) };
	m_objects.erase(newStart2, m_objects.end());
}
void Galaxy::DeleteFleet(Fleet_ty fleet) {
	m_fleets.erase(std::remove_if(m_fleets.begin(), m_fleets.end(),
		[fleet](Fleet_ty_c currentFleet) { return fleet->GetID() == currentFleet->GetID(); }));
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		[fleet](SpaceObject_ty const& object) { return fleet->GetID() == object->GetID(); }));
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

TargetPoint_ty Galaxy::GetTargetPointByID(unsigned int const ID) const {
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
// update
void Galaxy::UpdateFleetTargets(std::vector<Fleet_ty> fleets, SpaceObject_ty target) {
	for (auto const& fleet : fleets) {
		fleet->SetTarget(target);
	}
}

void Galaxy::CheckArrivingFriendlyFleets() {
	std::vector<Fleet_ty> toDelete{ };
	for (auto const& fleet : m_fleets) {
		bool const friendly{ fleet->GetTarget()->GetPlayer() == fleet->GetPlayer() };
		if (friendly and fleet->IsArrived()) {
			auto const& target = fleet->GetTarget();
			*target += *fleet;
			auto const origins{ GetFleetsOfTarget(fleet) };
			UpdateFleetTargets(origins, target);
			toDelete.push_back(fleet);
		}
	}
	DeleteFleet(toDelete);
}
void Galaxy::CheckMergingFriendlyFleets() {
	std::vector<std::pair<Fleet_ty_c, Fleet_ty_c>> same{ };
	auto const containsSame{ [&](Fleet_ty_c first, Fleet_ty_c second) {
		for (auto const& s : same) {
			if (s.first == first and s.second == second) { return true; }
			else if (s.first == second and s.second == first) { return true; }
		}
		return false;
	} };

	// find mergeable fleets
	for (int first = 0; first < m_fleets.size(); ++first) {
		for (int second = first + 1; second < m_fleets.size(); ++second) {
			auto const fleet1{ m_fleets.at(first) };
			auto const fleet2{ m_fleets.at(second) };

			bool const mergable{
				fleet1->GetPlayer() == fleet2->GetPlayer()
				and fleet1->GetPos() == fleet2->GetPos()
			};
			if (mergable and not containsSame(fleet1, fleet2)) {
				same.emplace_back(fleet1, fleet2);
			}
		}
	}
	if (same.size() == 0) { return; } // no found

	// merge fleets
	std::vector<Fleet_ty> toDelete{ };
	for (auto const& match : same) {
		*match.first += *match.second;
		auto const& origins{ GetFleetsOfTarget(match.second) };
		UpdateFleetTargets(origins, match.second->GetTarget());
		toDelete.push_back(match.second);
	}

	DeleteFleet(toDelete);
}
void Galaxy::CheckDeleteFleetsWithoutShips() {
	auto getFleets{ [&]() {
		std::vector<Fleet_ty> fleets{ };
		for (auto const& f : m_fleets) {
			if (f->GetShipCount() == 0) {
				fleets.push_back(f);
			}
		}
		return fleets;
	} };

	auto const& fleets{ getFleets() };
	if (fleets.size() == 0) { return; }

	for (auto const& f : fleets) {
		auto const& origins{ GetFleetsOfTarget(f) };
		UpdateFleetTargets(origins, f->GetTarget());
	}

	DeleteFleet(fleets);
}

// public
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

std::vector<TargetPoint_ty> const Galaxy::GetTargetPoints() const {
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
	auto const newStart{ std::remove_if(m_fleets.begin(), m_fleets.end(),
		[currentPlayerID](Fleet_ty_c fleet) { return fleet->GetPlayer()->GetID() != currentPlayerID; }) };
	m_fleets.erase(newStart, m_fleets.end());

	auto const newStart2{ std::remove_if(m_objects.begin(), m_objects.end(),
		[currentPlayerID](SpaceObject_ty_c object) { return object->IsFleet() and object->GetPlayer()->GetID() != currentPlayerID; }) };
	m_objects.erase(newStart2, m_objects.end());

	auto const newStart3{ std::remove_if(m_targetPoints.begin(), m_targetPoints.end(),
		[currentPlayerID](TargetPoint_ty_c targetPoint) { return targetPoint->GetPlayer()->GetID() != currentPlayerID; }) };
	m_targetPoints.erase(newStart3, m_targetPoints.end());

	auto const newStart4{ std::remove_if(m_objects.begin(), m_objects.end(),
		[currentPlayerID](SpaceObject_ty_c object) {return object->IsTargetPoint() and object->GetPlayer()->GetID() != currentPlayerID; }) };
	m_objects.erase(newStart4, m_objects.end());
}

void Galaxy::HandleFleetResult(FleetResult const& fleetResult) {
	auto add = [this](SpaceObject_ty_c obj) {
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
			auto const* t_p = dynamic_cast<TargetPoint_ty_raw>(obj.get());
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
	auto handle = [this, add](SpaceObject_ty_c obj) {
		if (obj) {
			auto& my_obj{ this->GetSpaceObjectByID(obj->GetID()) };
			if (my_obj) {
				my_obj->SetShipCount(obj->GetShipCount());
				if (my_obj->IsFleet()) {
					auto *const my_fleet{ dynamic_cast<Fleet *const>(&*my_obj) };
					auto const* const obj_fleet{ dynamic_cast<Fleet const* const>(&*obj) };
					if (obj_fleet) {
						my_fleet->SetTarget(obj_fleet->GetTarget());
					}
				}
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


// update
void Galaxy::Update() {
	for (auto& o : m_objects) {
		o->Update(this);
	}
	CheckArrivingFriendlyFleets();
	CheckMergingFriendlyFleets();
	CheckDeleteFleetsWithoutShips(); // Check bevor Fight so there will be no fight without ships
	// fight
	CheckDeleteFleetsWithoutShips(); // Check after fight so all fleets that lost there ships gets deleted.
}
