//
// Purpur Tentakel
// 14.09.2022
//

#include "Text.h"
#include "HTextProcessing.h"
#include "AppContext.h"
#include "HPrint.h"
#include <cassert>

void Text::CreateToRender() {
	std::vector<std::string> splitedText = BreakLines(m_text);
	std::vector<float> horizontalOffset = GetHorizontalAlignedOffset(splitedText, m_collider, m_textSize, m_textAlignment);
	std::vector<float> verticalOffset = GetVerticalAlignedOffset(splitedText, m_textSize, m_collider, m_textAlignment);

	assert(splitedText.size() == horizontalOffset.size());
	assert(splitedText.size() == verticalOffset.size());

	m_toRender.clear();
	for (int i = 0; i < splitedText.size(); ++i) {
		std::pair<std::string, Vector2> a =
			{ splitedText[i],{horizontalOffset[i] + m_collider.x, verticalOffset[i] + m_collider.y} };
		m_toRender.emplace_back(a);
	}
}
std::vector<std::string> Text::BreakLines(std::string toBreak) const {
	if (!m_lineBreaks) {
		return { toBreak };
	}

	std::vector<std::string> toReturn = BreakTextInVector(toBreak, m_textSize, m_collider.width);

	return toReturn;
}

void Text::OpenURL() const {
	if (!m_URL.empty()) {
		::OpenURL(m_URL.c_str());
	}
}

void Text::UpdateCollider() {
	UIElement::UpdateCollider();

	CreateToRender();
}

Text::Text(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Alignment textAlignment, float textHeight,
	std::string text)
	: UIElement(pos, size, alignment, resolution), m_textSize(textHeight * resolution.y),
	m_text(text), m_textHeight(textHeight), m_textAlignment(textAlignment) {

	CreateToRender();
}

void Text::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			OpenURL();
		}
	}
}
void Text::Render(AppContext const& appContext) {
	for (auto [text, position] : m_toRender) {
		DrawTextEx(
			*(appContext.assetManager.GetFont()),
			text.c_str(),
			position,
			m_textSize,
			0.0f,
			m_color
		);
	}

	if (m_renderRectangle) {
		DrawRectangleLinesEx(
			m_collider,
			1.0f,
			PURPLE
		);
	}
}
void Text::Resize(Vector2 resolution, AppContext const& appContext) {
	
	UIElement::Resize(resolution, appContext);
	m_textSize = m_textHeight * resolution.y;
	CreateToRender();
}

void Text::SetPosition(Vector2 pos) {

	UIElement::SetPosition(pos);

	CreateToRender();
}

void Text::SetSize(Vector2 size) {

	UIElement::SetSize(size);
	CreateToRender();
}

void Text::SetCollider(Rectangle collider) {

	UIElement::SetCollider(collider);
	CreateToRender();
}

float Text::GetRelativeTextHeight() {

	return m_textSize;
}

void Text::SetText(std::string text) {
	m_text = text;
	CreateToRender();
}
std::string Text::GetText() const {
	return m_text;
}

void Text::SetColor(Color color) {
	m_color = color;
}

Color Text::GetColor() const{
	return m_color;
}

void Text::SetURL(std::string URL) {
	StripString(URL);
	m_URL = URL;
}
void Text::ClearURL() {
	m_URL.clear();
}
std::string Text::GetURL() const {
	return m_URL;
}

void Text::LineBreaks(bool lineBreaks) {
	m_lineBreaks = lineBreaks;
	CreateToRender();
}
void Text::RenderRectangle(bool renderRectangle) {
	m_renderRectangle = renderRectangle;
}
