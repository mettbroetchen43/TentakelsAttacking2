//
// Purpur Tentakel
// 16.02.2022
//

#include "PlanetTable.h"
#include "Player.h"
#include "HFocusEvents.h"

void PlanetTable::Initialization() {
	auto const planets{ m_galaxy->GetPlanets() };

	m_table = std::make_shared<Table>(
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(1.0f, 1.0f),
		Alignment::TOP_LEFT,
		m_resolution,
		1000,
		static_cast<int>(planets.size() + 1),
		4,
		Vector2(0.25f, 0.05f),
		0.2f
	);
	m_table->SetAllEditable(false);
	m_table->SetFixedHeadline(true);
	m_table->SetScrollable(true);
	m_table->SetHighlightHover(true);
	m_table->SetHeadlineValues<std::string>({ "ID", "Player", "Production", "Ship Count" });
	m_elements.push_back(m_table);

	AppContext_ty_c appContext{ AppContext::GetInstance() };

	for (int i = 0; i < planets.size(); ++i) {
		auto planet = planets.at(i);

		// planet ID
		m_table->SetValue<int>(
			i + 1,
			0,
			planet->GetID()
		);

		// player name
		std::string entry;
		if (planet->IsDestroyed()) {
			entry = "DESTROYED";
		}
		else if (!planet->IsDiscovered()) {
			entry = "not discovered";
		}
		else {
			entry = appContext.playerCollection.GetPlayerOrNpcByID(planet->GetPlayer()->GetID()).name;
		}
		m_table->SetValue<std::string>(
			i + 1,
			1,
			entry
		);

		if (planet->IsDestroyed()) { continue; }
		if (!planet->IsDiscovered()) { continue; }

		// production
		m_table->SetValue<int>(
			i + 1,
			2,
			static_cast<int>(planet->GetProduction())
		);

		// ship count
		m_table->SetValue<int>(
			i + 1,
			3,
			static_cast<int>(planet->GetShipCount())
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
