//
// Purpur Tentakel
// 15.09.2022
//

#include "Picture.h"
#include "UIManager.h"
#include "AppContext.h"
#include <iostream>

Picture::Picture(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	AssetType assetType, bool scaleToFit)
	: UIElement{ pos, size, alignment, resolution }, m_isScaleToFit{ scaleToFit } {
	m_texture = AppContext::GetInstance().assetManager.GetTexture(assetType);

	if (m_isScaleToFit) {
		float const tempSize{ m_size.x };
		m_size.x =
			static_cast<float>(m_texture->width) / m_texture->height
			* resolution.y / resolution.x
			* m_size.y;
		m_pos.x -= (m_size.x - tempSize) / 2;
		UpdateCollider();
	}
}

void Picture::Render(AppContext_ty_c) {
	DrawTexturePro(
		*m_texture,
		Rectangle(
			0.0f,
			0.0f,
			static_cast<float>(m_texture->width),
			static_cast<float>(m_texture->height)
		),
		m_collider,
		Vector2(0.0f,0.0f),
		0.0f,
		WHITE
	);
}
