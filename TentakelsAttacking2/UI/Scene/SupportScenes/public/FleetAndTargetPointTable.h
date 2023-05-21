//
// Purpur Tentakel
// 15.05.2023
//

#include "Scene.h"
#pragma once

class Galaxy;
class Table;
template<typename T>
struct Vec2;

class FleetAndTargetPointTable final : public Scene {
private:
	Galaxy const* m_galaxy; ///< contains the current galaxy  of the logic
	std::shared_ptr<Table> m_table; ///< contains the table within the planet info's

	/**
	 * initializes the table from the current galaxy.
	 */
	void Initialization();

	/**
	 * returns the current position as a string.
	 */
	[[nodiscard]] std::string GetStringFromPosition(Vec2<int> position) const;

public:
	/**
	 * ctor and calls to initialize
	 */
	FleetAndTargetPointTable(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, Galaxy const* galaxy);
	/**
	 * sets if the scene is currently active.
	 * calls set focus active.
	 */
	void SetActive(bool active, AppContext const& appContext) override;
};
