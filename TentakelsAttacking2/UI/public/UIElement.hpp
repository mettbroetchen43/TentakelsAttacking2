//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "HSoundType.hpp"
#include "HAssetType.hpp"
#include "UIEvents.hpp"
#include "Allignment.h"
#include <raylib.h>


struct AppContext;

class UIElement {
protected:
	Vector2 m_pos, m_size;
	Vector2 m_resolution;
	Rectangle m_colider;
	Alignment m_alignment;

	void UpdateColider() {
		m_colider = {
			m_pos.x * m_resolution.x,
			m_pos.y * m_resolution.y,
			m_size.x * m_resolution.x,
			m_size.y * m_resolution.y
		};
	}
	void UpdateColiderReverse() {
		m_pos = {
			m_colider.x / m_resolution.x,
			m_colider.y / m_resolution.y
		};
		m_size = {
			m_colider.width / m_resolution.x,
			m_colider.height / m_resolution.y
		};
	}

public:
	UIElement(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution)
		: m_pos(pos), m_size(size), m_alignment(alignment), m_resolution(resolution) {
		
		m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	}
	virtual ~UIElement() = default;

	void SetPosition(Vector2 pos) {
		m_pos = pos;
		UpdateColider();
	}
	[[nodiscard]] Vector2 GetPosition() const {
		return m_pos;
	}
	void SetSize(Vector2 size) {
		m_size = size;
		UpdateColider();
	}
	[[nodiscard]] Vector2 GetSize() const {
		return m_size;
	}
	void SetResolution(Vector2 resolution) {
		m_resolution = resolution;
		UpdateColider();
	}
	[[nodiscard]] Vector2 GetResolution() const {
		return m_resolution;
	}
	virtual void SetCollider(Rectangle colider) {
		m_colider = colider;
		UpdateColiderReverse();
	}
	[[nodiscard]] Rectangle GetColider() const {
		return m_colider;
	}

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render(AppContext const& appContext) = 0;
	virtual void Resize(Vector2 resolution, AppContext const&) {
		m_resolution = resolution;
		UpdateColider();
	};
};