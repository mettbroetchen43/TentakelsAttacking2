//
// Purpur Tentakel
// 08.05.2023
//

#include "Hover.h"
#include "AppContext.h"
#include "UIEvents.hpp"

void Hover::CalculateDefault(AppContext const& appContext) {
	Vector2 const textOffset {
		m_resolution.x * 0.01f,
		m_resolution.y * 0.01f,
	};

	Vector2 const measure{ MeasureTextEx(
		*appContext.assetManager.GetFont(),
		m_text.c_str(),
		m_textHeight,
		0.0f
	) };

	Rectangle const newCollider{
		m_collider.x,
		m_collider.y,
		measure.x + textOffset.x,
		measure.y + textOffset.y
	};
	SetCollider(newCollider);

	m_textPosition = {
		m_collider.x + textOffset.x / 2,
		m_collider.y + textOffset.y / 2
	};
}

Hover::Hover(float height, std::string text, Color color, Vector2 hoverOffset, Vector2 resolution)
	: UIElement(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Alignment::BOTTOM_LEFT, resolution), m_color(color),
	m_hoverOffset{ hoverOffset }, m_text{ text }, m_textHeight{ height * resolution.y } {

	AppContext& appContext{ AppContext::GetInstance() };

	CalculateDefault(appContext);

	m_hoverTexture = appContext.assetManager.GetTexture(AssetType::GREY);
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
	Rectangle const newCollider{
		mousePosition.x + m_absoluteHoverOffset.x,
		mousePosition.y - m_absoluteHoverOffset.y - m_collider.height,
		m_collider.width,
		m_collider.height
	};
	SetCollider(newCollider);
	CalculateDefault(appContext);

	RenderHoverEvent event{ this };
	appContext.eventManager.InvokeEvent(event);
}

void Hover::Render(AppContext const& appContext) {
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
		m_color
	);
}
void Hover::Resize(Vector2 resolution, AppContext const& appContext) {
	UIElement::Resize(resolution, appContext);
	CalculateDefault(appContext);
}
