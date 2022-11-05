//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "HSoundType.hpp"
#include "HAssetType.hpp"
#include "UIEvents.hpp"
#include "Allignment.h"


struct AppContext;

class UIElement {
protected:
	Vector2 m_pos, m_size;
	Alignment m_alignment;

	virtual void UpdateColider(Vector2 resolution) = 0;

public:
	UIElement(Vector2 pos, Vector2 size, Alignment alignment)
		: m_pos(pos), m_size(size), m_alignment(alignment) { }
	virtual ~UIElement() = default;

	virtual void SetPosition(Vector2 pos, Vector2 resoltion) {
		m_pos = pos;
		UpdateColider(resoltion);
	}
	Vector2 GetPosition() const {
		return m_pos;
	}
	virtual void SetSize(Vector2 size, Vector2 resoltion) {
		m_size = size;
		UpdateColider(resoltion);
	}
	Vector2 GetSize() const {
		return m_size;
	}

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render(AppContext const& appContext) = 0;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) = 0;
};