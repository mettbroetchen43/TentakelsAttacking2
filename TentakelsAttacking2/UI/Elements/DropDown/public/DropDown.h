//
// Purpur Tentakel
// 01.12.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <memory>
#include <vector>

class DropDownElement;

class DropDown : public UIElement, public Focusable {
private:
	bool m_isEnabled = true; ///< contains if the element is currently enabled
	bool m_isFouldout = false; ///< contains if the element is currents folded out
	std::vector<std::shared_ptr<DropDownElement>> m_dropDownElements; ///< contains all elements in the drop down
	std::shared_ptr<DropDownElement> m_currentElement = nullptr; ///< contains the current element
	Rectangle m_fouldoutCollider; ///< contains the collider of the outfolded part

	/**
	 * initializes all ui elements.
	 * conntext the on click.
	 */
	void Initialize(std::vector<std::string const> const& elements);

	/**
	 * gets called of the elements as on click action.
	 */
	void OnElementClick() const;

	/**
	 * checks all elements if they are inside of the fouldoutCollider.
	 * sets the elements true if so else sets it false.
	 */
	void CheckIfElementsIsFouldoutCollider();

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	DropDown(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID,
		std::vector<std::string const> const& elements);


	/**
	 * returns the current element.
	 */
	[[nodiscard]] DropDownElement GetCurrentElement() const;
	/**
	 * sets the element of the provided ID as current element.
	 */
	void SetCurrentElementByID(unsigned int ID);


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
};
