//
// Purpur Tentakel
// 15.09.2022
//

#pragma once
#include "UIElement.hpp"

enum class AssetType;

class Picture final : public UIElement {
private:
	Texture2D* m_texture = nullptr;
	bool m_isScaleToFit = false;

public:
	Picture(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		AssetType assetType);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
};