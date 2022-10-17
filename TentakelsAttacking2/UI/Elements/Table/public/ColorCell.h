//
// Purpur Tentakel
// 02.10.2022
//

#pragma once
#include "Cell.h"

class ColorCell : public Cell {
private:
	Color m_value;

public:
	using Cell::Cell;

	[[nodiscard]] Vector2 GetNeededSize() const override;

	void SetValue(Color newColor, bool resize = false);
	[[nodiscard]] Color GetValue() const;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext) override;
};