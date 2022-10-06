//
// Purpur Tentakel
// 04.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

class DoubleCell;

class DoubleCellPopUp : public CellPopUp {
private:
	InputLine<double> m_inputChange;
	DoubleCell* m_currentCell;

	void Initialize(AppContext const& appContext) override;
	void SetValue() override;
	void CheckEnter() override;

public:
	DoubleCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, DoubleCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};