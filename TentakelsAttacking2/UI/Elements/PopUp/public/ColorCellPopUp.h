//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "PrimitiveCellPopUp.h"
#include "ColorPicker.h"

class ColorCell;

class ColorCellPopUp : public PrimitiveCellPopUp {
private:
	ColorPicker m_colorPicker;
	ColorCell* m_currentCell;

	void Initialize(AppContext const& appContext) override;
	void SetValue() override;
	void CheckEnter() override;

public:
	ColorCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, ColorCell* currentCell);

	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};