//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

class DropDownElement : public UIElement, public Focusable {
private:
	bool m_isEnabled = true; ///< contains if the element is currently enabled
	bool m_hover = false; ///< contains if the mouse if currently hovering over the element
	unsigned int m_ID; ///< contains the unique Element ID
	float m_fontSize; ///< contains the font height
	std::string m_toRender; ///< contains the string that gets rendered
	std::string m_text; ///< contains the raw string
	Vector2 m_textPosition; ///< contains the positon the text gets renderd at
	std::function<void(unsigned int)> m_onClick = [](unsigned int) {}; ///< contains the action that gets called on click or enter

	Texture* m_grey50; ///< contains a pointer to a texture in the appContext
	Rectangle m_textureRecGrey50; ///< contains the absolute dimensions of the texture

	/**
	 * generates the toRender string out of the raw string.
	 */
	void CreateToRender();

public:
	/**
	 * ctor.
	 * create toRender.
	 */
	DropDownElement(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		unsigned int focusID, unsigned int ID, std::string text);

	/**
	 * calls the CheckAndUpdate member function of the UIElement.
	 * contains the element logic.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext const&) override;
	/**
	 * renders the element.
	 */
	void Render(AppContext const& appContext) override;

	/**
	 * returns if the element is currently enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * sets if the element is currently enabled.
	 */
	void SetEnabled(bool isEnabled);

	/**
	 * sets the current text of the element.
	 */
	void SetText(std::string text);

	/**
	 * sets the lambda that gets calld on click or enter.
	 * provides the ID of the clicked element.
	 */
	void SetOnClick(std::function<void(unsigned int)> onClick);

	/**
	 * returns the element collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;
};