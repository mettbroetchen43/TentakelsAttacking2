//
// Purpur Tentakel
// 15.09.2022
//

#include "Picture.h"
#include "UIManager.h"
#include "AppContext.h"

Picture::Picture(Vector2 pos, Vector2 size, AssetType assetType, UIManager const& uiManager)
	: UIElement(pos, size) {

	m_texture = AppContext::GetInstance().assetManager.GetTexture(assetType);
	m_collider = {
		pos.x * uiManager.GetResolution().x,
		pos.y * uiManager.GetResolution().y,
		size.x * uiManager.GetResolution().x,
		size.y * uiManager.GetResolution().y
	};
}

void Picture::CheckAndUpdate([[maybe_unused]] Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) {
}
void Picture::Render(AppContext const& appContext) {
	DrawTexturePro(
		*m_texture,
		Rectangle (0.0f,0.0f,m_texture->width,m_texture->height),
		m_collider,
		Vector2(0.0f,0.0f),
		0.0f,
		WHITE
	);
}
void Picture::Resize(Vector2 resolution, AppContext const& appContext) {
	m_collider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
	if (m_isScaleToFit) {
		ScaleToFit();
	}
}

void Picture::ScaleToFit() {
	int ratio = m_texture->width / m_texture->height;
	m_collider.width = m_collider.height * ratio;
	m_isScaleToFit = true;
}

void Picture::SetTexture(AssetType assetType, bool scaleToFit) {
	m_texture = AppContext::GetInstance().assetManager.GetTexture(assetType);
	m_isScaleToFit = scaleToFit;
	if (m_isScaleToFit) {
		ScaleToFit();
	}
}
