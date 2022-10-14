//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <string>

class Text : public UIElement {
private:
	std::string m_text;
	std::string m_toRender;
	float m_textHeight;
	float m_textSize;
	Vector2 m_textPosition;

	Rectangle m_collider = { 0.0f,0.0f,0.0f,0.0f };
	bool m_lineBreaks = false;
	bool m_renderRectangle = false;

	void CreateToRender(AppContext const& appContext);
	std::string BreakLines(std::string toBreak, AppContext const& appContext) const;

public:
	Text(Vector2 pos, Vector2 size, Alignment alignment, float textHeight,
		std::string text, Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);

	void SetText(std::string text);
	std::string GetText() const;

	void LineBreaks(bool lineBreaks);
	void RenderRectangle(bool renderRectangle);
};