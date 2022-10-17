//
// Purpur Tentakel
// 02.10.2022
//

#pragma once
#include "Cell.h"

class DoubleCell : public TableCell {
private:
	double m_value;
public:
	using TableCell::TableCell;

	[[nodiscard]] Vector2 GetNeededSize() const override;
	[[nodiscard]] double GetValue() const;
	void SetValue(double newValue, bool resize = false);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext) override;
};