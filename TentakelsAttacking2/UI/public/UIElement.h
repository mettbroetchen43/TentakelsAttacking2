//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "SoundType.h"
#include "Events.h"
#include <raylib.h>

class AppContext;

class UIElement {
protected:
	Vector2 m_size, m_pos;

public:
	virtual ~UIElement() = default;
	UIElement(Vector2 size, Vector2 pos)
		: m_size(size), m_pos(pos) { }

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render() = 0;
	virtual void Resize(Vector2 resolution) = 0;
};