//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <string>

class Text final : public UIElement {
private:
	std::string m_text;
	std::string m_toRender;
	std::string m_URL = "";
	float m_textHeight;
	float m_textSize;
	Alignment m_textAlignment;
	Vector2 m_textPosition;

	Rectangle m_colider = { 0.0f,0.0f,0.0f,0.0f };
	bool m_lineBreaks = false;
	bool m_renderRectangle = false;

	void CreateToRender(AppContext const& appContext);
	std::string BreakLines(std::string toBreak, AppContext const& appContext) const;

	void UpdateColider(Vector2 resolution) override;

	void OpenURL() const;

public:
	Text(Vector2 pos, Vector2 size, Alignment alignment,
		Alignment textAlignment, float textHeight,
		std::string text, Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext);

	void SetText(std::string text);
	std::string GetText() const;

	void SetURL(std::string URL);
	void ClearURL();
	[[nodiscard]] std::string GetURL() const;

	void LineBreaks(bool lineBreaks);
	void RenderRectangle(bool renderRectangle);
};