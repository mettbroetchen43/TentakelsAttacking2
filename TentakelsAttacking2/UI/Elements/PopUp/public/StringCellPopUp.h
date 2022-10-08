//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "InputLine.hpp"

class StringCell;

class StringCellPopUp : public CellPopUp {
private:
	std::shared_ptr<InputLine<std::string>> m_inputChange;
	StringCell* m_currentCell;

	void Initialize(AppContext const& appContext,
		Vector2 resolution) override;
	void SetValue() override;
	void CheckEnter() override;

public:
	StringCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, StringCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};