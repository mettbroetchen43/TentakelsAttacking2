//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "ClassicButton.h"
#include "InputLine.h"

class StringCell;

class StringCellPopUp : public CellPopUp {
private:
	ClassicButton m_acceptBTN, m_cancelBTN;
	InputLine<std::string> m_inputChange;
	StringCell* m_currentCell;

	void Initialize(AppContext const& appCpntext);

public:
	StringCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string const& subTitle,
		AssetType infoTexture, StringCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};