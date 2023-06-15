//
// Purpur Tentakel
// 08.05.2023
//

#include "Hover.h"
#include "AppContext.h"
#include "UIEvents.hpp"

void Hover::CalculateDefault(AppContext_ty_c appContext) {
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

Vector2 Hover::GetRenderOffset() const {
	Vector2 renderOffset{ 0, 0 };
	if (m_collider.x + m_collider.width > m_resolution.x) {
		renderOffset.x = m_collider.x + m_collider.width - m_resolution.x;
	}
	if (m_collider.y < 0) {
		renderOffset.y = -m_collider.y;
	}

	return renderOffset;
}

Hover::Hover(float height, std::string text, Color color, Vector2 hoverOffset, Vector2 resolution)
	: UIElement(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), Alignment::BOTTOM_LEFT, resolution), m_color(color),
	m_hoverOffset{ hoverOffset }, m_text{ text }, m_textHeight{ height * resolution.y } {

	AppContext_ty appContext{ AppContext::GetInstance() };

	CalculateDefault(appContext);

	m_absoluteHoverOffset = {
		hoverOffset.x * m_resolution.x,
		hoverOffset.y * m_resolution.y
	};
}

void Hover::SetRenderHover(Vector2 mousePosition, AppContext_ty_c appContext) {
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

void Hover::SetText(std::string const& text) {
	m_text = { text };
}

void Hover::Render(AppContext_ty_c appContext) {
	auto const& renderOffset{ GetRenderOffset() };
	Rectangle const dummyCollider{
		m_collider.x - renderOffset.x,
		m_collider.y - renderOffset.y,
		m_collider.width,
		m_collider.height
	};
	Vector2 const dummyTextPosition{
		m_textPosition.x - renderOffset.x,
		m_textPosition.y - renderOffset.y
	};

	DrawRectangleRec(
		dummyCollider,
		GREY_100
	);
	DrawRectangleLinesEx(
		dummyCollider,
		2.0f,
		PURPLE
	);

	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_text.c_str(),
		dummyTextPosition,
		m_textHeight,
		0.0f,
		m_color
	);
}
void Hover::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	UIElement::Resize(resolution, appContext);
	CalculateDefault(appContext);
}
