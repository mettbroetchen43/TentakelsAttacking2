//
// Purpur Tentakel
// 14.09.2022
//

#include "Text.h"
#include "HTextProcessing.h"
#include "AppContext.h"
#include <cassert>

void Text::CreateToRender(AppContext const& appContext) {
	std::vector<std::string> splitedText = BreakLines(m_text, appContext);
	std::vector<float> horizontalOffset = GetHorisontalAlignedOffset(splitedText, m_collider, m_textSize, m_textAlignment);
	std::vector<float> verticalOffset = GetVerticalAlignedOffset(splitedText, m_textSize, m_collider, m_textAlignment);

	assert(splitedText.size() == horizontalOffset.size() == verticalOffset.size());

	m_toRender.clear();
	for (int i = 0; i < splitedText.size(); ++i) {
		std::pair<std::string, Vector2> a = { splitedText[i],{horizontalOffset[i],verticalOffset[i]} };
		m_toRender.emplace_back(a);
	}
}
std::vector<std::string> Text::BreakLines(std::string toBreak, AppContext const& appContext) const {
	if (!m_lineBreaks) {
		return { toBreak };
	}

	std::vector<std::string> toReturn = BreakTextInVector(toBreak, m_textSize, m_collider.width, appContext);

	return toReturn;
}

void Text::OpenURL() const {
	if (!m_URL.empty()) {
		::OpenURL(m_URL.c_str());
	}
}

void Text::UpdateCollider() {
	UIElement::UpdateCollider();

	CreateToRender(AppContext::GetInstance());
}

Text::Text(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Alignment textAlignment, float textHeight,
	std::string text)
	: UIElement(pos, size, alignment, resolution), m_textSize(textHeight * resolution.y),
	m_text(text), m_textHeight(textHeight), m_textAlignment(textAlignment) {

	CreateToRender(AppContext::GetInstance());
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
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_toRender.c_str(),
		m_textPosition,
		m_textSize,
		0.0f,
		m_color
	);
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
	CreateToRender(appContext);
}

void Text::SetPosition(Vector2 pos) {

	float diff = m_resolution.x * m_pos.x - m_resolution.x * pos.x;
	m_textPosition.x -= diff;

	diff = m_resolution.y * m_pos.y - m_resolution.y * pos.y;
	m_textPosition.y -= diff;

	UIElement::SetPosition(pos);
}

void Text::SetSize(Vector2 size) {

	UIElement::SetSize(size);
	CreateToRender(AppContext::GetInstance());
}

void Text::SetText(std::string text) {
	m_text = text;
	CreateToRender(AppContext::GetInstance());
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
	CreateToRender(AppContext::GetInstance());
}
void Text::RenderRectangle(bool renderRectangle) {
	m_renderRectangle = renderRectangle;
}
