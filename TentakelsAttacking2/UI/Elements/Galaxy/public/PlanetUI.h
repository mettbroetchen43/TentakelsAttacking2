//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "Player.h"

class PlanetUI : public UIElement {
private:
	unsigned int m_ID;
	std::string m_stringID;
	Color m_color;
	Rectangle m_colider;

	void UpdateColider(Vector2 resolution) override;

public:
	PlanetUI(Vector2 pos, unsigned int ID, Color color, Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	[[nodiscard]] unsigned int GetID() const;
	[[nodiscard]] Color GetColor() const;


};
