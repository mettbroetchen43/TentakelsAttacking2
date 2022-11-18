//
// Purpur Tentakel
// 06.10.2022
//

#pragma once
#include "UIElement.hpp"
#include <raylib.h>

class Line final : public UIElement {
private:
	float m_thick;

public:
	Line(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		float thick);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
};