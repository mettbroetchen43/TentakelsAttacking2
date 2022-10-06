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
	InputLine<std::string> m_inputChange;
	StringCell* m_currentCell;

	void Initialize(AppContext const& appContext) override;
	void SetValue() override;
	void CheckEnter() override;

public:
	StringCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, StringCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};