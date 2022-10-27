//
// Purpur Tentakel
// 15.09.2022
//

#include "Picture.h"
#include "UIManager.h"
#include "AppContext.h"

Picture::Picture(Vector2 pos, Vector2 size, Alignment alignment,
	AssetType assetType, Vector2 resolution)
	: UIElement(pos, size, alignment) {
	m_texture = AppContext::GetInstance().assetManager.GetTexture(assetType);
	m_size.x =
		static_cast<float>(m_texture->width) / m_texture->height
		* resolution.y / resolution.x
		* m_size.y;
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
}

void Picture::CheckAndUpdate([[maybe_unused]] Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) { }
void Picture::Render([[maybe_unused]] AppContext const& appContext) {
	DrawTexturePro(
		*m_texture,
		Rectangle (
			0.0f,
			0.0f,
			static_cast<float>(m_texture->width),
			static_cast<float>(m_texture->height)
		),
		m_colider,
		Vector2(0.0f,0.0f),
		0.0f,
		WHITE
	);
}
void Picture::Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) {
	m_colider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
}
