//
// Purpur Tentakel
// 08.05.2023
//

#include "UIElement.hpp"
#pragma once


class Hover final : public UIElement {
private:
	std::string m_text;
	Rectangle m_hoverTextureRec;
	Texture* m_hoverTexture;
	Vector2 m_hoverOffset;
	Vector2 m_absoluteHoverOffset;

	bool m_render = false;

	float m_textHeight;
	Vector2 m_textPosition;

	/**
	 * calculates textHeight, textPosition, colliderLength.
	 */
	void CalculateDefault(AppContext const& appContext);

public:
	/**
	 * ctor
	 */
	Hover(float height, std::string text, Vector2 hoverOffset, Vector2 resolution);

	/**
	 * sets the position to the mouse position.
	 * reders the hover.
	 */
	void SetRenderHover(Vector2 mousePosition, AppContext const& appContext);

	/**
	 * nothing
	 */
	void Render(AppContext const& appContext) override;

	/**
	 * rezises the argument
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;


};