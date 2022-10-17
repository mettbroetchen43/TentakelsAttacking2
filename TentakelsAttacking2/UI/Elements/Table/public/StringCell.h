//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "Cell.h"

class StringCell : public Cell {
private:
	std::string m_value;

public:
	using Cell::Cell;

	[[nodiscard]] Vector2 GetNeededSize() const override;
	[[nodiscard]] std::string GetValue() const;
	void SetValue(std::string newValue, bool resize = false);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};

