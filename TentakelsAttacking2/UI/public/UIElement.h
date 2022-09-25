//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "SoundType.h"
#include "AssetType.h"
#include "UIEvents.h"
#include "Allignment.h"


struct AppContext;

class UIElement {
protected:
	Vector2 m_pos, m_size;
	Alignment m_alignment;

public:
	virtual ~UIElement() = default;
	UIElement(Vector2 pos, Vector2 size, Alignment alignment)
		: m_pos(pos), m_size(size), m_alignment(alignment) { }

	Vector2 GetPosition() const {
		return m_pos;
	}
	Vector2 GetSize() const {
		return m_size;
	}

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render(AppContext const& appContext) = 0;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) = 0;
};