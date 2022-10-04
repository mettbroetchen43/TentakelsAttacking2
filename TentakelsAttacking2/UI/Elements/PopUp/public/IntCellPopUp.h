//
// Purpur Tentakel
// 04.10.2022
//

#pragma once
#include "PrimitiveCellPopUp.h"
#include "InputLine.h"

class IntCell;

class IntCellPopUp : public PrimitiveCellPopUp {
private:
	InputLine<int> m_inputChange;
	IntCell* m_currentCell;

	void Initialize(AppContext const& appContext) override;
	void SetValue() override;
	void CheckEnter() override;

public:
	IntCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string const& subTitle,
		AssetType infoTexture, IntCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};