//
// Purpur Tentakel
// 10.09.2022
//

#include "PopUp.h"
#include "AppContext.h"
#include <iostream>
#include <string>

void PopUp::Close() {
	AppContext& appContext = AppContext::GetInstance();
	auto event = ClosePopUpEvent(this);
	appContext.eventManager.InvokeEvent(event);
}

Vector2 PopUp::GetElementPosition(float x, float y) {
	return { m_pos.x + x * m_size.x, m_pos.y + y * m_size.y };
}
Vector2 PopUp::GetElementSize(float x, float y) {
	return { x * m_size.x, y * m_size.y };
}

Rectangle PopUp::GetColiderWithMaxValues(Texture2D* texture, float maxWidth, float maxHeight) const {

	if (maxWidth > texture->width and maxHeight > texture->height) {
		return { 0.0f, 0.0f, static_cast<float>(texture->width), static_cast<float>(texture->height) };
	}

	float ratio = static_cast<float>(texture->width) / static_cast<float>(texture->height);
	Rectangle rectangle(0.0f,0.0f,0.0f,0.0f);
	if (texture->width > maxWidth) {
		rectangle.width = maxWidth;
		rectangle.height = maxWidth * ratio;
	}
	if (texture->height > maxHeight) {
		rectangle.width = maxHeight * ratio;
		rectangle.height = maxHeight;
	}

	return rectangle;
}

PopUp::PopUp(Vector2 pos, Vector2 size, Vector2 resolution,
	std::string const& title, std::string const& subTitle,
	Texture2D* fullBackground, Texture2D* popUpBackground, Texture2D* infoTexture)
	: UIElement(pos, size), m_title(title), m_subTitle(subTitle),
	m_fullBackground(fullBackground), m_popUpBackground(popUpBackground), m_infoTexture(infoTexture) {
	m_backgroundColider = { 0.0f, 0.0f,  resolution.x, resolution.y };
	m_colider = { resolution.x * pos.x, resolution.y * pos.y , resolution.x * size.x, resolution.y * size.y };
}

void PopUp::Resize(Vector2 resolution,[[maybe_unused]] AppContext const& appContext) {
	m_backgroundColider = { 0.0f, 0.0f, resolution.x, resolution.y };
	m_colider = { resolution.x * m_pos.x, resolution.y * m_pos.y,
		resolution.x * m_size.x, resolution.y * m_size.y };
}
