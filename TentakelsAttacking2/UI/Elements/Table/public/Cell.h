//
// Purpur Tentakel
// 29.09.22
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <string>

class Table;

class Cell : public UIElement, public Focusable {
protected:
	Table* m_table;
	bool m_editable = true;
	Rectangle m_colider;
	Vector2 m_textPosition;
	float m_textSize;

	[[nodiscard]] bool ShouldEdit(Vector2 const& mousePosition) const;

public:
	Cell(Vector2 pos, Vector2 size, Alignment alignment,
		unsigned int ID, Vector2 resolution, Table* table);
	virtual ~Cell() = default;

	virtual void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext);
	virtual void Render(AppContext const& appContext) override;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) override;

	[[nodiscard]] Table* GetTable() const;

	void SetPosX(float posX);
	void SetPosY(float posY);

	[[nodiscard]] virtual Vector2 const& GetNeededSize() const = 0;
	void SetSizeX(float sizeX);
	void SetSizeY(float sizey);
	
	void SetEditable(bool editable);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;
};