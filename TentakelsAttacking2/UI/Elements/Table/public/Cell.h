//
// Purpur Tentakel
// 29.09.22
//

#pragma once
#include "UIElement.h"
#include "Focusable.h"
#include <string>

class Cell : public UIElement, public Focusable {
private:
protected:
	Rectangle m_colider;
	Vector2 m_textPosition;
	float m_textSize;

	[[nodiscard]] bool ShouldEdit(Vector2 const& mousePosition) const;

public:
	Cell(Vector2 pos, Vector2 size, Alignment alignment,
		unsigned int ID, Vector2 resolution);
	virtual ~Cell() = default;

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	virtual void Render(AppContext const& appContext) override;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) override;
	
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;
};