//
// Purpur Tentakel
// 15.05.2023
//

#include "FleetAndTargetPointTable.h"
#include "Table.h"
#include "HFocusEvents.h"
#include "Text.h"
#include "Galaxy.h"

void FleetAndTargetPointTable::Initialization() {
	auto const fleets{ m_galaxy->GetFleets() };
	auto const targetPoints{ m_galaxy->GetTargetPoints() };
	int constexpr startFleets{ 2 };
	int const startTargetPoints{ startFleets + (fleets.size() > 0 ? static_cast<int>(fleets.size()) : 1) + 1 };
	int const tableSize{ startTargetPoints + (targetPoints.size() > 0 ? static_cast<int>(targetPoints.size()) : 1) };

	m_table = std::make_shared<Table>(
		GetElementPosition(0.0f, 0.0f),
		GetElementSize(1.0f, 1.0f),
		Alignment::TOP_LEFT,
		m_resolution,
		1000,
		tableSize,
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

	m_table->SetValue<std::string>(1, 0, "Fleets:");
	if (fleets.size() > 0) {
		for (int i = 0; i < fleets.size(); ++i) {
			auto const fleet{ fleets.at(i) };

			// fleet ID
			m_table->SetValue<int>(
				i + startFleets,
				0,
				fleet->GetID()
			);

			// position
			std::string const pos{ GetStringFromPosition(fleet->GetPos()) };
			m_table->SetValue<std::string>(
				i + startFleets,
				1,
				pos
			);

			// count
			m_table->SetValue<int>(
				i + startFleets,
				2,
				static_cast<int>(fleet->GetShipCount())
			);

			// destination
			auto const destination{ fleet->GetTarget() };
			std::string dest;
			if (destination->IsPlanet()) {
				dest = "Planet " + std::to_string(destination->GetID());
			}
			else if (destination->IsFleet()) {
				dest = "Fleet " + std::to_string(destination->GetID());
			}
			else if (destination->IsTargetPoint()) {
				dest = "Target Point x: " + std::to_string(fleet->GetTarget()->GetPos().x) + " | y: " + std::to_string(fleet->GetTarget()->GetPos().y);
			}
			else {
				dest = "Invalid Destination";
			}
			m_table->SetValue<std::string>(
				i + startFleets,
				3,
				dest
			);
		}
	}
	else {
		m_table->SetValue<std::string>(startFleets, 0, "no Fleets available");
	}

	m_table->SetValue<std::string>(startTargetPoints-1, 0, "Target Points:");
	if (targetPoints.size() > 0) {
		for (int i = 0; i < targetPoints.size(); ++i) {
			auto const targetPoint{ targetPoints.at(i) };

			// target point ID
			m_table->SetValue<int>(
				i + startTargetPoints,
				0,
				targetPoint->GetID()
			);

			// position
			std::string const pos{ GetStringFromPosition(targetPoint->GetPos()) };
			m_table->SetValue<std::string>(
				i + startTargetPoints,
				1,
				pos
			);

			// count
			m_table->SetValue<int>(
				i + startTargetPoints,
				2,
				static_cast<int>(targetPoint->GetShipCount())
			);

			m_table->SetValue<std::string>(
				i + startTargetPoints,
				3,
				"---"
			);
		}
	}
	else {
		m_table->SetValue<std::string>(startTargetPoints, 0, "no target points available");
	}
}

std::string FleetAndTargetPointTable::GetStringFromPosition(Vec2<int> position) const {

	for (auto const& p : m_galaxy->GetPlanets()) {
		auto const& pos{ p->GetPos() };
		if (pos == position) {
			return "Planet " + std::to_string(p->GetID());
		}
	}

	return "x: " + std::to_string(position.x)
		+ " | y: " + std::to_string(position.y);
}

FleetAndTargetPointTable::FleetAndTargetPointTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Galaxy const* galaxy)
	: Scene{ pos, size, alignment, resolution }, m_galaxy{ galaxy } {

	Initialization();
}

void FleetAndTargetPointTable::SetActive(bool active, AppContext const& appContext) {

	if (active == m_active) { return; }

	if (m_table->IsNestedFocus() && !active) {
		DeleteFocusLayer();
		m_table->SetNestedFocus(false);
	}
	Scene::SetActive(active, appContext);
}
