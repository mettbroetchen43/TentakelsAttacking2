//
// Purpur Tentakel
// 02.10.2022
//

#pragma once
#include "Cell.h"

class FloatCell : public TableCell {
private:
	float m_value;
public:
	using TableCell::TableCell;

	[[nodiscard]] Vector2 GetNeededSize() const override;
	[[nodiscard]] float GetValue() const;
	void SetValue(float newValue, bool resize = false);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext) override;
};
