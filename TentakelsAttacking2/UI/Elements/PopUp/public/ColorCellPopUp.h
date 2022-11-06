//
// Purpur Tentakel
// 05.10.2022
//

#pragma once
#include "CellPopUp.h"
#include "ColorPicker.h"

class ColorCellPopUp final : public CellPopUp {
private:
	std::shared_ptr<ColorPicker> m_colorPicker;
	std::function<void(Color)> m_onClick = [](Color) {};

	void Initialize(AppContext const& appContext,
		Vector2 resolution, Color currentColor);
	void SetValue() override;

public:
	ColorCellPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, AssetType infoTexture, Color currentColor,
		std::function<void(Color)> onClick);
};