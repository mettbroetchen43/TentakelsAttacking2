//
// Purpur Tentakel
// 08.05.2023
//

#include "Hover.h"
#include "AppContext.h"

void Hover::CalculateDefault(AppContext const& appContext) {
	m_textHeight = m_collider.height / 2;

	Vector2 measure = MeasureTextEx(
		*appContext.assetManager.GetFont(),
		m_text.c_str(),
		m_textHeight,
		0.0f
	);

	Rectangle newCollider = {
		m_collider.x,
		m_collider.y,
		measure.x + m_textHeight,
		m_collider.height
	};

	m_textPosition = {
		m_collider.x + m_textHeight / 2,
		m_collider.y + m_textHeight / 2 * 3
	};
}

Hover::Hover(float height, std::string text, Vector2 hoverOffset, Vector2 resolution)
	: UIElement(Vector2(0.0f, 0.0f), Vector2(0.0f, height), Alignment::BOTTOM_LEFT, resolution), m_hoverOffset(hoverOffset), m_text(text) {

	AppContext& appContext = AppContext::GetInstance();

	CalculateDefault(appContext);

	m_hoverTexture = appContext.assetManager.GetTexture(AssetType::GREY_50);
	m_hoverTextureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_hoverTexture->width),
		static_cast<float>(m_hoverTexture->height)
	};

	m_absoluteHoverOffset = {
		hoverOffset.x * m_resolution.x,
		hoverOffset.y * m_resolution.y
	};
}

void Hover::SetRenderHover(Vector2 mousePosition, AppContext const& appContext) {
	Rectangle newCollider {
		mousePosition.x + m_absoluteHoverOffset.x,
		mousePosition.y - m_absoluteHoverOffset.y - m_collider.height,
		m_collider.width,
		m_collider.height
	};
	SetCollider(newCollider);
	CalculateDefault(appContext);
	m_render = true;
}

void Hover::Render(AppContext const& appContext) {
	if (not m_render) { return; }

	DrawTexturePro(
		*m_hoverTexture,
		m_hoverTextureRec,
		m_collider,
		Vector2(0.0f, 0.0f),
		0.0f,
		WHITE
	);
	DrawRectangleLinesEx(
		m_collider,
		2.0f,
		PURPLE
	);

	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_text.c_str(),
		m_textPosition,
		m_textHeight,
		0.0f,
		WHITE
	);
	m_render = false;
}
void Hover::Resize(Vector2 resolution, AppContext const& appContext) {
	UIElement::Resize(resolution, appContext);
	CalculateDefault(appContext);
}
