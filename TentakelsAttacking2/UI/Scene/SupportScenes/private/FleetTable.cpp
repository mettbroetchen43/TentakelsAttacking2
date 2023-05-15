//
// Purpur Tentakel
// 15.05.2023
//

#include "FleetTable.h"
#include "Table.h"
#include "HFocusEvents.h"
#include "Text.h"
#include "Galaxy.h"

void FleetTable::Initialisation() {
	auto fleets = m_galaxy->GetFleets();

	m_table = std::make_shared<Table>(
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(1.0f, 1.0f),
		Alignment::TOP_LEFT,
		m_resolution,
		100,
		static_cast<int>(fleets.size() + 1),
		4,
		Vector2(0.25f, 0.05f),
		0.2f
	);
	m_table->SetAllEditable(false);
	m_table->SetFixedHeadline(true);
	m_table->SetScrollable(true);
	m_table->SetHighlightHover(true);
	m_table->SetHeadlineValues<std::string>({ "ID", "Position", "Ship Count", "Destination" });
	m_elements.push_back(m_table);

	AppContext& appContext = AppContext::GetInstance();

	for (int i = 0; i < fleets.size(); ++i) {
		auto fleet = fleets.at(i);
		
		// fleet ID
		m_table->SetValue<int>(
			i + 1,
			0,
			fleet->GetID()
		);

		// position
		std::string pos = "x: " + std::to_string(fleet->GetPos().x) + " | y: " + std::to_string(fleet->GetPos().y);
		m_table->SetValue<std::string>(
			i + 1,
			1,
			pos
		);

		// count
		m_table->SetValue<int>(
			i + 1,
			2,
			fleet->GetShipCount()
		);

		// destination
		auto destination = fleet->GetTarget();
		std::string dest{ };
		if (destination->IsPlanet()) {
			dest = "Planet " + std::to_string(destination->GetID());
		}
		else if (destination->IsFleet()) {
			dest = "Fleet " + std::to_string(destination->GetID());
		}
		else if (destination->IsTargetPoint()) {
			dest = "Target Point x: " + std::to_string(fleet->GetPos().x) + " | y: " + std::to_string(fleet->GetPos().y);
		}
		else {
			dest = "Invalid Destination";
		}
		m_table->SetValue<std::string>(
			i + 1,
			3,
			dest
		);
	}
}

FleetTable::FleetTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Galaxy const* galaxy)
	: Scene(pos, size, alignment, resolution), m_galaxy(galaxy) {

	Initialisation();
}

void FleetTable::SetActive(bool active, AppContext const& appContext) {

	if (active == m_active) { return; }

	if (m_table->IsNestedFocus() && !active) {
		DeleteFocusLayer();
		m_table->SetNestedFocus(false);
	}
	Scene::SetActive(active, appContext);
}
