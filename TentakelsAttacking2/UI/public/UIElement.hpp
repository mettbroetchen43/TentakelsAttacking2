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

/**
 * provides the basic UIElement.
 * all elements
 */
class UIElement {
protected:
	Vector2 m_pos, m_size; ///< contains the realtive position (top left) and size on the screen
	Vector2 m_resolution; ///< contains the current resolution of the window
	Rectangle m_colider;  ///< contains the absolute position (top left) and size on the screen
	Alignment m_alignment; ///< contains the alignment of the element

	/**
	 * calculates the absolute position and size out of the relative position and size and the current resolution.
	 */
	void UpdateColider() {
		m_colider = {
			m_pos.x * m_resolution.x,
			m_pos.y * m_resolution.y,
			m_size.x * m_resolution.x,
			m_size.y * m_resolution.y
		};
	}
	/**
	 * calculates the relative position and size out of the absolute position and size and the current resolution.
	 */
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
	/**
	 * ctor.
	 * calls the aligned collider.
	 */
	UIElement(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution)
		: m_pos(pos), m_size(size), m_alignment(alignment), m_resolution(resolution) {
		
		m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	}
	/**
	 * default virtual dtor.
	 */
	virtual ~UIElement() = default;

	/**
	 * sets a new relative position.
	 * calls to update the collider.
	 */
	virtual void SetPosition(Vector2 pos) {
		m_pos = pos;
		UpdateColider();
	}
	/**
	 * returns the current relative position. 
	 */
	[[nodiscard]] Vector2 GetPosition() const {
		return m_pos;
	}
	/**
	 * sets a new relative size.
	 * calls to update the collider.
	 */
	virtual void SetSize(Vector2 size) {
		m_size = size;
		UpdateColider();
	}
	/**
	 * returns the current relative size.
	 */
	[[nodiscard]] Vector2 GetSize() const {
		return m_size;
	}
	/**
	 * sets a new resolution.
	 */
	void SetResolution(Vector2 resolution) {
		m_resolution = resolution;
		UpdateColider();
	}
	/**
	 *  returns the current resolution.
	 */
	[[nodiscard]] Vector2 GetResolution() const {
		return m_resolution;
	}
	/**
	 * sets a new absolute position and size.
	 * calles to update the relative position and size.
	 */
	virtual void SetCollider(Rectangle colider) {
		m_colider = colider;
		UpdateColiderReverse();
	}
	/**
	 * returns the current absolute position and size.
	 */
	[[nodiscard]] Rectangle GetCollider() const {
		return m_colider;
	}

	/**
	 * moves the element to a certain point in one second.
	 * need to call this multiple times.
	 * REIMPLEMENT! ISSUE ON GIT.
	 */
	virtual void Move(Vector2 pos) {
		float time = GetFrameTime();
		float diffX = (m_pos.x - pos.x) * time;
		float diffY = (m_pos.y - pos.y) * time;

		SetPosition(Vector2(
			m_pos.x - diffX,
			m_pos.y - diffY
		));
	}

	/**
	 * just virtual.
	 * to implement.
	 * should contain the logic of the element.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	/**
	 * just virtual.
	 * to implement.
	 * should render the element.
	 */
	virtual void Render(AppContext const& appContext) = 0;
	/**
	 * sets new resolution.
	 * cals update collider.
	 */
	virtual void Resize(Vector2 resolution, AppContext const&) {
		m_resolution = resolution;
		UpdateColider();
	};
};