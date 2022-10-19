//
// Purpur Tentakel
// 10.09.2022
//

#include "PopUp.h"
#include "Picture.h"
#include "Text.h"
#include "HGeneral.h"
#include "HTextProcessing.h"
#include "AppContext.h"
#include <iostream>
#include <string>

void PopUp::Initialize(std::string const& title, std::string& subTitle,
	AssetType infoTexture, Vector2 resolution) {
	
	auto globalBackground = std::make_shared<Picture>(
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 1.0f),
		Alignment::DEFAULT,
		AssetType::GREY_50,
		resolution
		);
	m_elements.push_back(globalBackground);

	auto background = std::make_shared<Picture>(
		m_pos,
		m_size,
		Alignment::DEFAULT,
		AssetType::GREY,
		resolution
		);
	m_elements.push_back(background);

	auto icon = std::make_shared<Picture>(
		GetElementPosition(m_pos, m_size, 0.15f, 0.05f),
		GetElementSize(m_size, 0.25f, 0.3f),
		Alignment::TOP_MID,
		infoTexture,
		resolution
		);
	m_elements.push_back(icon);

	auto textTitle = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.6f, 0.1f),
		GetElementSize(m_size, 0.7f, 0.2f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		GetElementTextHight(m_size, 0.2f),
		title,
		resolution
		);
	m_elements.push_back(textTitle);

	float textHeight = GetElementTextHight(m_size, 0.1f);
	BreakText(
		subTitle,
		textHeight,
		m_size.x * resolution.x,
		AppContext::GetInstance()
	);

	auto textSubTitle = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.5f, 0.4f),
		GetElementSize(m_size, 0.9f, 0.4f),
		Alignment::TOP_MID,
		Alignment::TOP_MID,
		textHeight,
		subTitle,
		resolution
		);
	m_elements.push_back(textSubTitle);
}
void PopUp::LateUpdate() {
	if (m_firstEnter and IsKeyUp(KEY_ENTER)) {
		m_firstEnter = false;
	}
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
	std::string const& title, std::string& subTitle, AssetType infoTexture)
	: UIElement(pos, size, alignment) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	
	Initialize(title, subTitle, infoTexture, resolution);

	if (IsKeyDown(KEY_ENTER)) {
		m_firstEnter = true;
	}
}

void PopUp::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}
void PopUp::Render(AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Render(appContext);
	}

	DrawRectangleLinesEx(
		m_colider,
		2.0f,
		PURPLE
	);
}
void PopUp::Resize(Vector2 resolution, AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}
