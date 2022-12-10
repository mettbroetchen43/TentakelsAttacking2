//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <memory>
#include <vector>
#include <functional>

class DropDownElement;

class DropDown : public UIElement, public Focusable {
private:
	bool m_isEnabled = true; ///< contains if the element is currently enabled
	bool m_isFouldout = false; ///< contains if the element is currents folded out
	bool m_isScolling = true; ///< countais if the DropDown in able to scroll
	std::vector<std::shared_ptr<DropDownElement>> m_dropDownElements; ///< contains all elements in the drop down
	
	Texture const* m_arrowTexture; ///< contains the texture of the arrow that conntrols if the menu is droped down
	Rectangle m_arrowTextureRec; ///< contains the dimensions onto the texture
	Rectangle m_arrowCollider; ///< contains the absolute domensions of the arrow

	std::shared_ptr<DropDownElement> m_currentElement = nullptr; ///< contains the current element
	std::string m_currentElementText = ""; ///< contains the text of the current element
	float m_fontSize = 0.0f; ///< contains the height of the text of the current element
	Vector2 m_textPosition = { 0.0f,0.0f }; ///< contains the position of the current element
	
	float m_dropDownHeight; ///< contains the relative height of the drop down part
	Rectangle m_dropDownCollider; ///< contains the collider of the drop down part
	std::function<void(unsigned int)> m_onSave = [](unsigned int) {}; ///< gets called of save

	/**
	 * initializes all ui elements.
	 * conntext the on click.
	 */
	void Initialize(std::vector<std::string> const& elements, unsigned int startFocusID);
	/**
	 * gets called of the elements as on click action.
	 */
	void OnElementClick(unsigned int ID);
	
	/**
	 * sets the current element and current element text.
	 */
	void SetCurrentElement(std::shared_ptr<DropDownElement> element);

	/**
	 * toggles the drop down menu.
	 */
	void ToggleFoldedOut();

	/**
	 * calculates a collider that represets the area where the provided collider
	 * overlaps with the drop down collider.
	 * returns the themorary collider.
	 */
	[[nodiscard]] Rectangle GetTemporaryCollider(Rectangle collider) const;

	/**
	 * checks if the elements in overaping with the drop down collider.
	 * sets the element active if so.
	 * sets it inactive if not.
	 */
	void CheckAndSetElementsEnabled();

	/**
	 * scrolls the entries an sets new focused entry if nececary.
	 * the movment value gets multipleyed ba the wheel value.
	 */
	void Scroll(float wheel);
	/**
	 * clampes the first and last value into the drop down collider.
	 */
	void ClampScrolling();
	/**
	 * Checks if scolling should be enabled.
	 */
	void CheckIfScolling();
public:
	/**
	 * ctor.
	 * only initialization.
	 */
	DropDown(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, float dropDownSize, 
		unsigned int focusID, unsigned int startElementFocusID, std::vector<std::string> const& elements);


	/**
	 * returns the current element.
	 */
	[[nodiscard]] std::shared_ptr<DropDownElement> GetCurrentElement() const;
	/**
	 * sets the element of the provided ID as current element.
	 * returns if the element was set.
	 */
	bool SetCurrentElementByID(unsigned int ID);


	/**
	 * calls the CheckAndUpdate of the UIElement.
	 * contains the DropDown logic.
	 */
	void CheckAndUpdate(Vector2 const&, AppContext const&) override;
	/**
	 * renders the DropDown.
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
	 * returns the current collider of the element.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * sets the lambda that gets called when a value gets set.
	 * provides the element ID when it gets called.
	 */
	void SetOnSave(std::function<void(unsigned int)> onSave);
};
