//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "ColorPicker.h"

class ColorCell;

class ColorCellPopUp : public CellPopUp {
private:
	std::shared_ptr<ColorPicker> m_colorPicker;
	ColorCell* m_currentCell;

	void Initialize(AppContext const& appContext,
		Vector2 resolution) override;
	void SetValue() override;

public:
	ColorCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, ColorCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};