//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include <raylib.h>

class UIElement {
private:
	Vector2 m_size, m_pos, m_resolution;

public:
	virtual ~UIElement() = default;
	UIElement(Vector2 size, Vector2 pos, Vector2 resolution)
		: m_size(size), m_pos(pos), m_resolution(resolution) { }

	virtual void CheckAndUpdate(Vector2 const& mousePosition) = 0;
	virtual void Render() = 0;
	virtual void Resize(Vector2 resolution) = 0;
};