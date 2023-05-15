//
// Purpur Tentakel
// 15.05.2023
//

#include "Scene.h"
#pragma once

class Galaxy;
class Table;

class FleetTable final : public Scene {
private:
	Galaxy const* m_galaxy; ///< contains the current galaxy  of the logic
	std::shared_ptr<Table> m_table; ///< contains the table within the planet infos

	void Initialisation();

public:
	FleetTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Galaxy const* galaxy);
	void SetActive(bool active, AppContext const& appContext) override;
};
