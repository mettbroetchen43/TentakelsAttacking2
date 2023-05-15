//
// Purpur Tentakel
// 16.02.2022
//

#pragma once
#include "Scene.h"
#include "Galaxy.h"
#include "Table.h"

class PlanetTable final : public Scene {
private:
	Galaxy const* m_galaxy; ///< contains the current galaxy  of the logic
	std::shared_ptr<Table> m_table; ///< contains the table within the planet infos

	void Initialisation();

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	PlanetTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		Galaxy const* galaxy);

	/**
	 * sets if the scene is currently active.
	 * calls set focus active.
	 */
	void SetActive(bool active, AppContext const& appContext) override;
};
