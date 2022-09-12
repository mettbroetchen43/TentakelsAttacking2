//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "SoundType.h"
#include "AssetType.h"
#include "Events.h"
#include <raylib.h>

struct AppContext;

class UIElement {
protected:
	Vector2 m_pos, m_size;

public:
	virtual ~UIElement() = default;
	UIElement(Vector2 pos, Vector2 size)
		: m_pos(pos), m_size(size) { }

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render(AppContext const& appContext) = 0;
	virtual void Resize(Vector2 resolution) = 0;
};