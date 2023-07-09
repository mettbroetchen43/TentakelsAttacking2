//
// Purpur Tentakel
// 10.09.2022
//

#include "PopUp.h"
#include "Picture.h"
#include "Text.h"
#include "HGeneral.h"
#include "HInput.h"
#include "HTextProcessing.h"
#include "AppContext.h"
#include <string>

void PopUp::Initialize(std::string const& title, std::string& subTitle,
	AssetType infoTexture, Vector2 resolution) {
	
	auto icon = std::make_shared<Picture>(
		GetElementPosition(m_pos, m_size, 0.15f, 0.05f),
		GetElementSize(m_size, 0.25f, 0.3f),
		Alignment::TOP_MID,
		resolution,
		infoTexture
		);
	m_elements.push_back(icon);

	auto textTitle = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.6f, 0.1f),
		GetElementSize(m_size, 0.7f, 0.2f),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_MID,
		GetElementTextHeight(m_size, 0.18f),
		title
		);
	m_elements.push_back(textTitle);

	float textHeight = GetElementTextHeight(m_size, 0.1f);
	BreakText(
		subTitle,
		textHeight * m_resolution.y,
		m_size.x * resolution.x * 0.9f,
		AppContext::GetInstance()
	);

	auto textSubTitle = std::make_shared<Text>(
		GetElementPosition(m_pos, m_size, 0.5f, 0.4f),
		GetElementSize(m_size, 0.9f, 0.4f),
		Alignment::TOP_MID,
		resolution,
		Alignment::TOP_MID,
		textHeight,
		subTitle
		);
	textSubTitle->LineBreaks(true);
	m_elements.push_back(textSubTitle);
}
void PopUp::LateUpdate() {
	if (m_firstEnter and IsKeyUp(KEY_ENTER)) {
		m_firstEnter = false;
	}
}

Rectangle PopUp::GetColliderWithMaxValues(Texture2D* texture, float maxWidth, float maxHeight) const {

	if (maxWidth > texture->width and maxHeight > texture->height) {
		return { 0.0f, 0.0f, static_cast<float>(texture->width), static_cast<float>(texture->height) };
	}

	float const ratio{ static_cast<float>(texture->width) / static_cast<float>(texture->height) };
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
	: UIElement{ pos, size, alignment, resolution } {
	
	Initialize(title, subTitle, infoTexture, resolution);

	if (IsConfirmInputDown()) {
		m_firstEnter = true;
	}
}

void PopUp::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	for (auto const& e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}

	if (m_shouldClose) {
		appContext.eventManager.InvokeEvent(ClosePopUpEvent(this));
	}
}
void PopUp::Render(AppContext_ty_c appContext) {
	DrawRectangleRec(
		Rectangle(
			0.0f,
			0.0f,
			m_resolution.x,
			m_resolution.y
		),
		GREY_50
	);
	DrawRectangleRec(m_collider, GREY_100);

	for (auto const& e : m_elements) {
		e->Render(appContext);
	}

	DrawRectangleLinesEx(
		m_collider,
		2.0f,
		PURPLE
	);
}
void PopUp::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	for (auto const& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}
