//
// Purpur Tentakel
// 17.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"

class AbstractTableCell : public UIElement, public Focusable {
protected:
	Rectangle m_colider;

	void CheckResizeCells(Vector2 resolution,
		AppContext const& appContext, bool resize);

public:
	AbstractTableCell(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment);
	virtual ~AbstractTableCell() = default;

	[[nodiscard]] virtual Vector2 GetNeededSize() = 0 ;

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) = 0;
	virtual void Render(AppContext const& appContext) = 0;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) = 0;

	virtual void SetEditable(bool editable) = 0;
	[[nodiscard]] virtual bool IsEnabled() const = 0;
	[[nodiscard]] virtual Rectangle GetCollider() const = 0;

	void SetPosX(float posX, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
	void SetPosY(float posY, Vector2 resolution,
		AppContext const& appContext, bool resize = true);

	void SetSizeX(float sizeX, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
	void SetSizeY(float sizeY, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
};
