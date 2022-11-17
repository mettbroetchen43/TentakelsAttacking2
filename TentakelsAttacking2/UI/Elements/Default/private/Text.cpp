//
// Purpur Tentakel
// 14.09.2022
//

#include "Text.h"
#include "HTextProcessing.h"
#include "AppContext.h"

void Text::CreateToRender(AppContext const& appContext) {
	m_toRender = BreakLines(m_text, appContext);
	m_toRender = GetHorisontalAlignedText(m_toRender, m_colider, m_textSize, m_textAlignment);
	m_textPosition = GetVerticalAlignedTextPosition(m_toRender, m_textSize, m_colider, m_textAlignment);
}
std::string Text::BreakLines(std::string toBreak, AppContext const& appContext) const {
	if (!m_lineBreaks) {
		return toBreak;
	}

	BreakText(toBreak, m_textSize, m_colider.width, appContext);

	return toBreak;
}

void Text::OpenURL() const {
	if (!m_URL.empty()) {
		::OpenURL(m_URL.c_str());
	}
}

Text::Text(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Alignment textAlignment, float textHeight,
	std::string text)
	: UIElement(pos, size, alignment, resolution), m_textSize(textHeight * resolution.y),
	m_text(text), m_textHeight(textHeight), m_textAlignment(textAlignment) {

	CreateToRender(AppContext::GetInstance());
}

void Text::CheckAndUpdate(Vector2 const& mousePosition, AppContext const&) {
	if (CheckCollisionPointRec(mousePosition, m_colider)) {
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
		WHITE
	);
	if (m_renderRectangle) {
		DrawRectangleLinesEx(
			m_colider,
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

	UIElement::SetPosition(pos);
	CreateToRender(AppContext::GetInstance());
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
