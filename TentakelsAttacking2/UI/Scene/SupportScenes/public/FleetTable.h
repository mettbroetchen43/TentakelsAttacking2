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

	/**
	 * initializes the table from the current galaxy.
	 */
	void Initialization();

public:
	/**
	 * ctor and calls to initialize
	 */
	FleetTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Galaxy const* galaxy);
	/**
	 * sets if the scene is currently active.
	 * calls set focus active.
	 */
	void SetActive(bool active, AppContext const& appContext) override;
};
