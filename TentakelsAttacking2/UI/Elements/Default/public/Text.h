//
// Purpur Tentakel
// 14.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <string>

/**
 * displayes a text in a collider that can be allignet. 
 */
class Text final : public UIElement {
private:
	using render_ty = std::vector<std::pair<std::string const, Vector2>>;
	std::string m_text; ///< contains the raw string that was set to the text
	render_ty m_toRender;///< contains the modified string that gets renderd and the position of each line
	std::string m_URL = ""; ///< contains an URL that can be opend by klick
	float m_textHeight; ///< contains the absolute textheight in px
	float m_textSize; ///< contains the relativ text size
	Alignment m_textAlignment; ///< contains the text alignemnt
	Color m_color = WHITE; ///< contains the color the text will be rendered in

	bool m_lineBreaks = false; ///< contains if the text is automaticly breaks in multiple lines
	bool m_renderRectangle = false; ///< contains if the collider will be rendered

	/**
	 * generates a printable version if the raw string.
	 * that contains the alignment and the line breaks.
	 */
	void CreateToRender(AppContext const& appContext);
	/**
	 * calls a helper function that replayes some whatespace with \n.
	 * returns directly if the linebreak is deactivated.
	 */
	std::vector<std::string> BreakLines(std::string toBreak, AppContext const& appContext) const;

	/**
	 * opens the provided URL if one is provided.
	 * else nothing happens.
	 */
	void OpenURL() const;

	/**
	 * calls UpdateCollider of the UIElement.
	 * updates the text position.
	 */
	void UpdateCollider() override;

public:
	/**
	 * ctor.
	 * calls to generate to render.
	 */
	Text(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		Alignment textAlignment, float textHeight,
		std::string text);

	/**
	 * text logic.
	 * in perticular if it gets pressed.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	/**
	 * renders the text.
	 */
	void Render(AppContext const& appContext);
	/**
	 * resizes the text.
	 * creates a not render string.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext);

	/**
	 * updates the text position and the collider.
	 */
	void SetPosition(Vector2 pos) override;
	/**
	 * updates the text size and the collider.
	 */
	void SetSize(Vector2 size) override;

	/**
	 * sets a new raw string.
	 * generates a new render string.
	 */
	void SetText(std::string text);
	/**
	 * returns the raw string.
	 */
	[[nodiscard]] std::string GetText() const;

	/**
	 * sets the text color.
	 */
	void SetColor(Color color);
	/**
	 * returns the text color.
	 */
	[[nodiscard]] Color GetColor() const;

	/**
	 * sets the text url.
	 */
	void SetURL(std::string URL);
	/**
	 * clears the text url.
	 */
	void ClearURL();
	/**
	 * returns the text url.
	 */
	[[nodiscard]] std::string GetURL() const;

	/**
	 * sets if the line Beaks are generated.
	 * cenerates a new render string.
	 */
	void LineBreaks(bool lineBreaks);
	/**
	 * sets if the collider gets renderd.
	 */
	void RenderRectangle(bool renderRectangle);
};