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
	Rectangle rectangle(0.0f, 0.0f, 0.0f, 0.0f);
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

PopUp::PopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	std::string const& title, std::string const& subTitle, AssetType infoTexture)
	: UIElement(pos, size, alignment), m_title(title), m_subTitle(subTitle) {
	AppContext& appContext = AppContext::GetInstance();

	m_fullBackground  = appContext.assetManager.GetTexture(AssetType::GREY_50);
	m_popUpBackground = appContext.assetManager.GetTexture(AssetType::GREY);
	m_infoTexture     = appContext.assetManager.GetTexture(infoTexture);

	m_backgroundColider = {
		0.0f,
		0.0f,
		resolution.x,
		resolution.y
	};

	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
}

void PopUp::Render(AppContext const& appContext) {
	Rectangle textureRec = { 0.0f,0.0f,
	static_cast<float>(m_fullBackground->width), static_cast<float>(m_fullBackground->height) };
	DrawTexturePro(*m_fullBackground, textureRec, m_backgroundColider, { 0.0f, 0.0f }, 0, WHITE);

	textureRec = { 0.0f, 0.0f, static_cast<float>(m_popUpBackground->width),static_cast<float>(m_popUpBackground->height) };
	DrawTexturePro(*m_popUpBackground, textureRec, m_colider, { 0.0f, 0.0f }, 0, WHITE);
	DrawRectangleLines(
		static_cast<int>(m_colider.x),
		static_cast<int>(m_colider.y),
		static_cast<int>(m_colider.width),
		static_cast<int>(m_colider.height), PURPLE);

	textureRec = { 0.0f, 0.0f,
	static_cast<float>(m_infoTexture->width),static_cast<float>(m_infoTexture->height) };
	Rectangle colider = GetColiderWithMaxValues(m_infoTexture, m_colider.width * 0.3f,
		m_colider.height * 0.3f);
	colider.x = m_colider.x + m_colider.width * 0.075f;
	colider.y = m_colider.y + m_colider.height * 0.025f;
	DrawTexturePro(*m_infoTexture, textureRec, colider, { 0.0f, 0.0f }, 0.0f, WHITE);

	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_title.c_str(),
		Vector2(m_colider.x + m_colider.width * 0.3f, m_colider.y + m_colider.height * 0.1f),
		m_colider.height * 0.2f,
		0,
		WHITE);
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_subTitle.c_str(),
		Vector2(m_colider.x + m_colider.width * 0.05f, m_colider.y + m_colider.height * 0.40f),
		m_colider.height * 0.1f,
		0,
		WHITE);
}

void PopUp::Resize(Vector2 resolution, [[maybe_unused]] AppContext const& appContext) {
	m_backgroundColider = { 0.0f, 0.0f, resolution.x, resolution.y };
	m_colider = { resolution.x * m_pos.x, resolution.y * m_pos.y,
		resolution.x * m_size.x, resolution.y * m_size.y };
}
