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

Text::Text(Vector2 pos, Vector2 size, Alignment alignment,
	Alignment textAlignment, float textHeight,
	std::string text, Vector2 resolution)
	: UIElement(pos, size, alignment), m_textSize(textHeight * resolution.y),
	m_text(text), m_textHeight(textHeight), m_textAlignment(textAlignment) {
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);
	CreateToRender(AppContext::GetInstance());
}

void Text::CheckAndUpdate([[maybe_unused]] Vector2 const& mousePosition,
	[[maybe_unused]] AppContext const& appContext) { }
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
	m_colider = {
		m_pos.x * resolution.x,
		m_pos.y * resolution.y,
		m_size.x * resolution.x,
		m_size.y * resolution.y
	};
	m_textSize = m_textHeight * resolution.y;
	CreateToRender(appContext);
}

void Text::SetText(std::string text) {
	m_text = text;
	CreateToRender(AppContext::GetInstance());
}
std::string Text::GetText() const {
	return m_text;
}

void Text::LineBreaks(bool lineBreaks) {
	m_lineBreaks = lineBreaks;
	CreateToRender(AppContext::GetInstance());
}
void Text::RenderRectangle(bool renderRectangle) {
	m_renderRectangle = renderRectangle;
}
