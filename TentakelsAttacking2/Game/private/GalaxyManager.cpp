//
// PurpurTentakel
// 23.05.23
//

#include "GalaxyManager.h"
#include "Galaxy.h"
#include "CopyGalaxyType.hpp"
#include "AppContext.h"
#include "Vec2.hpp"
#include "GenerelEvents.hpp"
#include "HPrint.h"
#include "Player.h"
#include "GameManager.h"

void GalaxyManager::FilterCurrentGalaxy() {
	std::shared_ptr<Player> currentPlayer{ nullptr };
	bool const valid{ m_gameManager->GetCurrentPlayer(currentPlayer) };
	if (not valid) { return; }
	m_currentGalaxy->FilterByPlayer(currentPlayer->GetID());
}

GalaxyManager::GalaxyManager(GameManager* gameManager)
	: m_gameManager {gameManager} { }

void GalaxyManager::GenerateGalaxy() {
	AppContext const& appContext{ AppContext::GetInstance() };
	Vec2<int> const size = {
		appContext.constants.world.currentDimensionX,
		appContext.constants.world.currentDimensionY
	};
	auto const galaxy = std::make_shared<Galaxy>(
		size,
		appContext.constants.world.currentPlanetCount,
		m_gameManager->m_players,
		m_gameManager->m_npcs[PlayerType::NEUTRAL]
	);

	if (galaxy->IsValid()) {
		m_mainGalaxy = galaxy;
		CopyGalaxies(CopyGalaxyType::COPY_ALL);
		GalaxyGeneratedUIEvent const event{ };
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		ShowMessagePopUpEvent const event{
			"Galaxy",
			"Unable to generate the Galaxy.\nTo many Plantes.",
			[]() {}
		};
		appContext.eventManager.InvokeEvent(event);
	}
}
void GalaxyManager::GenerateShowGalaxy() {
	AppContext const& appContext{ AppContext::GetInstance() };
	Vec2<int> const size = {
		appContext.constants.world.showDimensionX,
		appContext.constants.world.showDimensionY,
	};

	auto const galaxy = std::make_shared<Galaxy>(
		size,
		appContext.constants.world.showPlanetCount,
		m_gameManager->m_players,
		m_gameManager->m_npcs[PlayerType::NEUTRAL]
	);

	if (galaxy->IsValid()) {
		m_showGalaxy = galaxy;
		SendGalaxyPointerEvent const event{ m_showGalaxy.get(), true };
		appContext.eventManager.InvokeEvent(event);
	}
	else if (m_showGalaxy) {
		SendGalaxyPointerEvent const event{ m_showGalaxy.get(), true };
		appContext.eventManager.InvokeEvent(event);
		Print("Could not generated ShowGalaxy -> Use old Galaxy", PrintType::EXPECTED_ERROR);
	}
	else {
		Print("Could not generated ShowGalaxy -> No Galaxy", PrintType::ERROR);
	}
}

void GalaxyManager::CopyGalaxies(CopyGalaxyType copyType) {
	if (copyType == CopyGalaxyType::COPY_ALL) {
		m_startGalaxy = std::make_shared<Galaxy>(*m_mainGalaxy);
	}
	m_currentGalaxy = std::make_shared<Galaxy>(*m_startGalaxy);
	FilterCurrentGalaxy();
}

Galaxy* GalaxyManager::GetGalaxy() const {
	return m_currentGalaxy.get();
}

bool GalaxyManager::AddFleet(SendFleetInstructionEvent const* event, std::shared_ptr<Player> currentPlayer) {

	auto const [isValidFleet, generated_vec] {m_mainGalaxy->AddFleet(event, currentPlayer)};
	if (not isValidFleet) {
		Print("Not able to add Fleet to current Galaxy", PrintType::ERROR);

		ReturnFleetInstructionEvent const returnEvent{ isValidFleet };
		AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
		return false;
	}

	for (auto& g : generated_vec) {
		bool const valid{ m_currentGalaxy->AddSpaceObjectImmediately(g) };
		if (not valid) { Print("not able to add generated SpaceObjects to current Galaxy", PrintType::ERROR); }
	}

	return true;
}
