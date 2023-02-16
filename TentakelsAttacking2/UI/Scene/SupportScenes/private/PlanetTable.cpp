//
// Purpur Tentakel
// 16.02.2022
//

#include "PlanetTable.h"
#include "Player.h"
#include "HFocusEvents.h"

PlanetTable::PlanetTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Galaxy const* galaxy)
	: Scene(pos, size, alignment, resolution), m_galaxy(galaxy) {

	auto planets = m_galaxy->GetPlanets();

	m_table = std::make_shared<Table>(
		100,
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(1.0f, 1.0f),
		Alignment::TOP_LEFT,
		m_resolution,
		planets.size() + 1,
		4
	);
	m_table->SetAllCellsEditable(false);
	m_table->SetHeadlines({ "ID", "Player", "Producton", "Ship Count" });
	m_elements.push_back(m_table);

	AppContext const& appContext = AppContext::GetInstance();

	for (int i = 0; i < planets.size(); ++i) {
		auto planet = planets.at(i);

		// planet ID
		m_table->SetValue<int>(
			i + 1,
			0,
			planet->GetID(),
			false
		);

		// player name
		std::string entry;
		if (planet->IsDestroyed()) {
			entry = "DESTROYED";
		}
		else if (!planet->IsDescovered()) {
			entry = "not descovered";
		}
		else {
			entry = appContext.playerCollection.GetPlayerOrNpcByID(planet->GetPlayer()->GetID()).name;
		}
		m_table->SetValue<std::string>(
			i + 1,
			1,
			entry,
			false
			);

		if (planet->IsDestroyed()) { continue; }
		// if (!planet->IsDescovered()) { continue; }

		// production
		m_table->SetValue<int>(
			i + 1,
			2,
			static_cast<int>(planet->GetProduction()),
			false
		);

		// ship count
		m_table->SetValue<int>(
			i + 1,
			3,
			static_cast<int>(planet->GetShipCount()),
			false
		);
	}
}

void PlanetTable::SetActive(bool active, AppContext const& appContext) {

	if (active == m_active) { return; }

	if (m_table->IsNestedFocus() && !active) {
		DeleteFocusLayer();
		m_table->SetNestedFocus(false);
	}
	Scene::SetActive(active, appContext);
}
