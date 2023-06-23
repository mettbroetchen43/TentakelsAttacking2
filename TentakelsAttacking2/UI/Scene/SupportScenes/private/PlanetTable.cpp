//
// Purpur Tentakel
// 16.02.2022
//

#include "PlanetTable.h"
#include "Player.h"
#include "HFocusEvents.h"

void PlanetTable::Initialization() {
	auto const planets{ m_galaxy->GetPlanets() };
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	int discoveredCount{ 0 };
	for (auto const& p : planets) {
		if (p->IsDiscovered()) { ++discoveredCount; }
	}

	m_table = std::make_shared<Table>(
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(1.0f, 1.0f),
		Alignment::TOP_LEFT,
		m_resolution,
		1000,
		discoveredCount + 1,
		4,
		Vector2(0.25f, 0.05f),
		0.2f
	);
	m_table->SetAllEditable(false);
	m_table->SetFixedHeadline(true);
	m_table->SetScrollable(true);
	m_table->SetHighlightHover(true);
	m_table->SetHeadlineValues<std::string>({
		appContext.languageManager.Text("ui_planet_table_headline_id"),
		appContext.languageManager.Text("ui_planet_table_headline_player"),
		appContext.languageManager.Text("ui_planet_table_headline_production"),
		appContext.languageManager.Text("ui_planet_table_headline_ship_count")});
	m_elements.push_back(m_table);

	int addedCount{ 0 };
	for (auto const& p : planets) {
		//testing
		if (discoveredCount == addedCount) { break; }
		if (not p->IsDiscovered()) { continue; }
		else{ ++addedCount; }

		// planet ID
		m_table->SetValue<int>(
			addedCount,
			0,
			p->GetID()
		);

		// player name
		std::string entry;
		if (p->IsDestroyed()) {
			entry = appContext.languageManager.Text("ui_planet_table_player_name_destroyed");
		}
		else if (!p->IsDiscovered()) {
			entry = appContext.languageManager.Text("ui_planet_table_player_name_not_discovered");
		}
		else {
			entry = appContext.playerCollection.GetPlayerOrNpcByID(p->GetPlayer()->GetID()).GetName();
		}
		m_table->SetValue<std::string>(
			addedCount,
			1,
			entry
		);

		if (p->IsDestroyed()) { continue; }
		if (!p->IsDiscovered()) { continue; }

		// production
		m_table->SetValue<int>(
			addedCount,
			2,
			static_cast<int>(p->GetProduction())
		);

		// ship count
		m_table->SetValue<int>(
			addedCount,
			3,
			static_cast<int>(p->GetShipCount())
		);
	}
}

PlanetTable::PlanetTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Galaxy_ty_raw galaxy)
	: Scene{ pos, size, alignment, resolution }, m_galaxy{ galaxy } {
	
	Initialization();
}

void PlanetTable::SetActive(bool active, AppContext_ty_c appContext) {

	if (active == m_active) { return; }

	if (m_table->IsNestedFocus() && !active) {
		DeleteFocusLayer();
		m_table->SetNestedFocus(false);
	}
	Scene::SetActive(active, appContext);
}
