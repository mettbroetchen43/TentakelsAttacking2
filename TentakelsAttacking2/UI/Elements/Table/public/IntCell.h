//
// Purpur Tentakel
// 29.09.22
//

#pragma once
#include "Cell.h"

class IntCell : public Cell {
private:
protected:
public:
	int value = 0;

	using Cell::Cell;

	[[nodiscard]] Vector2 GetNeededSize() const override;
	[[nodiscard]] int GetValue() const;
	void SetValue(int newValue, bool resize = false);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};