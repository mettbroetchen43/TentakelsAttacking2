//
// Purpur Tentakel
// 08.05.2023
//

#include "UIElement.hpp"
#pragma once


class Hover final : public UIElement {
private:
	std::string m_text; ///< contains the Hover text
	Color m_color; ///< contains the render text color
	Rectangle m_hoverTextureRec; ///< contains the size of the texute
	Texture* m_hoverTexture; ///< contains the hover background
	Vector2 m_hoverOffset; ///< contans the offset between mouse and recangle in decimal
	Vector2 m_absoluteHoverOffset; ///< contains the offset between mouse and rectangle in px

	float m_textHeight; ///< contains text size in px
	Vector2 m_textPosition; ///< contains the text position in px

	/**
	 * calculates textHeight, textPosition, colliderLength.
	 */
	void CalculateDefault(AppContext const& appContext);

public:
	/**
	 * ctor
	 */
	Hover(float height, std::string text, Color color, Vector2 hoverOffset, Vector2 resolution);

	/**
	 * sets the position to the mouse position.
	 * reders the hover.
	 */
	void SetRenderHover(Vector2 mousePosition, AppContext const& appContext);

	/**
	 * renders the hover.
	 * gets called from HoverRender
	 */
	void Render(AppContext const& appContext) override;

	/**
	 * rezises the argument
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;


};