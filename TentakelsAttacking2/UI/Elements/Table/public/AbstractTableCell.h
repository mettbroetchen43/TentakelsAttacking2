//
// Purpur Tentakel
// 17.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"

class AbstractTableCell : public UIElement, public Focusable {
protected:
	bool m_editable = true;

	void CheckResizeCells(Vector2 resolution,
		AppContext const& appContext, bool resize);

public:
	AbstractTableCell(unsigned int ID, Vector2 pos, Vector2 size,
		Alignment alignment, Vector2 resolution);
	virtual ~AbstractTableCell() = default;

	[[nodiscard]] virtual Vector2 GetNeededSize() = 0 ;

	void SetEditable(bool editable);
	[[nodiscard]] bool IsEnabled() const override;

	[[nodiscard]] Rectangle GetCollider() const;

	void SetPosX(float posX, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
	void SetPosY(float posY, Vector2 resolution,
		AppContext const& appContext, bool resize = true);

	void SetSizeX(float sizeX, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
	void SetSizeY(float sizeY, Vector2 resolution,
		AppContext const& appContext, bool resize = true);
};
