//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "UIElement.hpp"
#include <raylib.h>

class Line : public UIElement {
private:
	float m_thick;
	Rectangle m_colider;

public:
	Line(Vector2 pos, Vector2 size, Alignment alignment,
		float thick, Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);
};