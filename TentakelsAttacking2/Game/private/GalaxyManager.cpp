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
#include "HFleetResult.hpp"

void GalaxyManager::FilterCurrentGalaxy() {
	Player_ty currentPlayer{ nullptr };
	bool const valid{ m_gameManager->GetCurrentPlayer(currentPlayer) };
	if (not valid) { return; }
	m_mainGalaxy->SetDiscoverByPlayer(currentPlayer->GetID());
	m_currentGalaxy->SetDiscoverByPlayer(currentPlayer->GetID());
	m_currentGalaxy->FilterByPlayer(currentPlayer->GetID());
}

GalaxyManager::GalaxyManager(GameManager* gameManager)
	: m_gameManager {gameManager} { }

void GalaxyManager::GenerateGalaxy() {
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	vec2pos_ty_c size = {
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
			appContext.languageManager.Text("logic_galaxy_manager_unable_generate_galaxy_title"),
			appContext.languageManager.Text("logic_galaxy_manager_unable_generate_galaxy_text", "\n"),
			[]() {}
		};
		appContext.eventManager.InvokeEvent(event);
	}
}
void GalaxyManager::GenerateShowGalaxy() {
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	vec2pos_ty_c size = {
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

Galaxy* GalaxyManager::GetGalaxy() {
	if (m_currentGalaxy and not m_currentGalaxy->IsFiltrered()) {
		FilterCurrentGalaxy();
	}
	return m_currentGalaxy.get();
}

bool GalaxyManager::AddFleet(SendFleetInstructionEvent const* event, Player_ty currentPlayer) {

	auto const result {m_mainGalaxy->AddFleet(event, currentPlayer)};
	if (not result.valid) {
		Print("Not able to add Fleet to main Galaxy", PrintType::INFO);

		ReturnFleetInstructionEvent const returnEvent{ result.valid };
		AppContext::GetInstance().eventManager.InvokeEvent(returnEvent);
		return false;
	}
	m_currentGalaxy->HandleFleetResult(result);

	return true;
}

UpdateResult_ty GalaxyManager::Update() {
	return m_mainGalaxy->Update();
}
