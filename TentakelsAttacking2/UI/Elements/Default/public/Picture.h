//
// Purpur Tentakel
// 15.09.2022
//

#pragma once
#include "UIElement.hpp"

enum class AssetType;
class UIManager;

class Picture : public UIElement {
private:
	Texture2D* m_texture = nullptr;
	Rectangle m_collider = { 0.0f,0.0f,0.0f,0.0f };
	bool m_isScaleToFit = false;

public:
	Picture(Vector2 pos, Vector2 size, Alignment alignment,
		AssetType assetType, UIManager const& uiManager);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);
};