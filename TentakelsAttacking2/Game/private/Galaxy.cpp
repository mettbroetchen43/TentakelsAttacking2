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
#include <stdexcept>

// help Labmdas
static auto popup = [](std::string const& text) {
    auto popupEvent = ShowMessagePopUpEvent("Invalid Input", text);
    AppContext::GetInstance().eventManager.InvokeEvent(popupEvent);
};
static auto message = [](std::string& messageText, std::string const& first, std::string const& second) {
    if (messageText.size() <= 0) { messageText = first; return; }

    messageText += ", " + second;
};

unsigned int Galaxy::GetNextID() const {

    if (m_objects.empty()) { return 1; }

    unsigned int nextID = 1;
    while (true) {
        bool freeID = true;
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

void Galaxy::InitialzePlanets(size_t planetCount,
    std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> neutralPlayer) {
    
    int currentPlanet = GenerateHomePlanets(players);
    if (m_validGalaxy) {
        GenerateOtherPlanets(planetCount, currentPlanet, neutralPlayer);
    }
}
int Galaxy::GenerateHomePlanets(std::vector<std::shared_ptr<Player>> players) {

    Random& random = Random::GetInstance();
    AppContext& appContext = AppContext::GetInstance();
    int currentPlanet = 1; 



    for (auto& p : players) {
        int counter = 0;
        while (true) {
            Vec2<int> newPosition = {
               static_cast<int>(random.random(m_size.x)),
               static_cast<int>(random.random(m_size.y))
            };

            auto newPlanet = std::make_shared<Planet>(
                GetNextID(),
                newPosition,
                p,
                true,
                currentPlanet
                );

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

    AppContext& appContext = AppContext::GetInstance();
    Random& random = Random::GetInstance();


    for (;currentPlanet <= planetCount; ++currentPlanet) {
        int counter = 0;
        while (true) {
            Vec2<int> newPosition = {
                static_cast<int>(random.random(m_size.x)),
                static_cast<int>(random.random(m_size.y))
            };

            auto newPlanet = std::make_shared<Planet>(
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
    int validPlanet = true;

    // works because Home Planets are generated first.
    float factor = newPlanet->IsHomePlanet()
        ? appContext.constants.planet.homeworldSpacing
        : appContext.constants.planet.globalSpacing;
    double spacing = m_size.Length() * factor;

    for (auto& p : m_planets) {
        double currentSpacing = (p->GetPos() - newPlanet->GetPos()).Length();
        if (currentSpacing < spacing) {
            validPlanet = false;
            break;
        }
    }

    return validPlanet;
}

// Fleet
bool Galaxy::AddFleetFromPlanet(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {

    // check origin id
    if (event->GetOrigin() > m_planets.size()) {
        popup("input for planet in origin to high");
        return false;
    }

    // check origin
    auto currentPlanet = GetPlanetByID(static_cast<unsigned int>(event->GetOrigin()));
    if (currentPlanet->GetPlayer() != currentPlayer) {
        popup("the choosen origin isn't your Planet.");
        return false;
    }
    if (currentPlanet->GetShipCount() < event->GetShipCount()) {
        popup("not enough ships on planet " + std::to_string(event->GetOrigin()));
        return false;
    }

    // get destination
    auto destination = GetOrGenerateDestination(
        event->GetDestination(),
        event->GetDestinationX(),
        event->GetDestinationY(),
        currentPlayer
    );
    
    return true;
}

bool Galaxy::AddFleetFromFleet(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer)
{
    return false;
}

bool Galaxy::AddFleetFromTargetPoint(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer)
{
    return false;
}

std::shared_ptr<SpaceObject> Galaxy::GetOrGenerateDestination(unsigned int ID,
    unsigned int X, unsigned int Y, std::shared_ptr<Player> currentPlayer) {

    for (auto& object : m_objects) {

        if (object->GetID() == ID) { return object; }

        auto pos = object->GetPos();
        if (pos.x == X && pos.y == Y) {
            if (object->GetPlayer() == currentPlayer) {
                return object;
            }
        }
    }

    Print("TODO generate target point for destination", PrintType::DEBUG);
}

Galaxy::Galaxy(Vec2<int> size, size_t planetCount,
    std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Player> neutralPlayer)
    : m_size(size) {

    InitialzePlanets(planetCount, players, neutralPlayer);
}
Galaxy::Galaxy(Galaxy const& old)
    : m_validGalaxy(old.m_validGalaxy), m_objects(old.m_objects),
    m_planets(old.m_planets), m_size(old.m_size) { }

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

bool Galaxy::AddFleet(SendFleedInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {

    // valid ID?
    if(!IsValidSpaceObjectID(event->GetOrigin())){
        popup("ID not existing as origin: " + std::to_string(event->GetOrigin()));
        return false;
    }
    if(!IsValidSpaceObjectID(event->GetDestination())){

        bool validCoordinates =
            (event->GetDestinationX() > 0
                && event->GetDestinationX() <= m_size.x)
            && (event->GetDestinationY() > 0
                && event->GetDestinationY() <= m_size.y);
        bool coordinateInput =
            event->GetDestinationX() > 0 && event->GetDestinationY() > 0;

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

    auto const& origin = GetSpaceObjectByID(event->GetOrigin());

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
