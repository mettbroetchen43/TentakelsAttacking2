//
// Purpur Tentakel
// 04.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

class FloatCell;

class FloatCellPopUp : public CellPopUp {
private:
	std::shared_ptr<InputLine<float>> m_inputChange;
	FloatCell* m_currentCell;

	void Initialize(AppContext const& appContext,
		Vector2 resolution) override;
	void SetValue() override;
	void CheckEnter() override;

public:
	FloatCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, FloatCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};
