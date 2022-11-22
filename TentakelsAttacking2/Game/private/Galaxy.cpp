//
// PurpurTentakel
// 08.11.22
//

#include "Galaxy.h"
#include "AppContext.h"
#include "Player.h"
#include "HRandom.h"
#include "UIEvents.hpp"

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

Vec2<int> Galaxy::GetSize() const {
    return m_size;
}
std::vector<std::shared_ptr<Planet>> const Galaxy::GetPlanets() const {
    return m_planets;
}
