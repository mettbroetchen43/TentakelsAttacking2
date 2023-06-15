//
// Purpur Tentakel
// 15.06.2023
//

#pragma once
#include "UIElement.hpp"
#include "HPlayerData.hpp"
#include "Focusable.h"
#include "Hover.h"

class UIGalaxyElement : public UIElement, public Focusable {
protected:
	unsigned int m_ID; ///< contains the unique SpaceObject ID witch is also the SpaceObject "name"
	std::string m_stringID; ///< contains the ID as string
	bool m_isEnabled{ true }; ///< contains if the element is enabled
	Vector2 m_colliderPos; ///< the position of the collider
	PlayerData m_currentPlayer; ///< contains the current player data that own the SpaceObject
	Color m_color; ///< contains the current color.
	std::function<void(UIPlanet*)> m_onClick{ [](UIPlanet*) {} }; ///< contains on click that gets called when the planet is clicked
	Hover m_hover; ///< contains the hover element
	bool m_renderHover{ false }; ///< contains if the hover text should be rendered

public:
	/**
	 * ctor.
	 * converts the id to a string.
	 */
	UIGalaxyElement(unsigned int focusID, unsigned int ID, PlayerData player, Vector2 pos, Vector2 resolution,
		Vector2 colliderPos);

	/**
	 * Updates the position with the collider position.
	 */
	void UpdatePosition(Rectangle newColider);

	/**
	 * updates the hover text
	 */
	virtual void UpdateHoverText() = 0;

	/**
	 * sets the onClick lambda that ´gets called when the planet is clicked.
	 * provides this.
	 */
	void SetOnClick(std::function<void(UIPlanet*)> onClick);

	/**
	 * sets a player the planet ist currently owning.
	 */
	void SetPlayer(PlayerData player);

	/**
	 * returns the current player of the UIPlanet.
	 */
	[[nodiscard]] PlayerData GetPlayer() const;

	/** 
	 * sets a new color.
 	 */
	void SetColor(Color color);
	/**
	 * returns the current color.
	 */

	[[nodiscard]] Color GetColor() const;
	/**
	 * returns the unique id.
	 */
	[[nodiscard]] unsigned int GetID() const;

	/**
	 * returns if the mouse is currently over the planet.
	 */
	[[nodiscard]] bool IsHover() const;

	/**
	 * sets if the planets is enabled.
	 */
	void SetEnabled(bool isEnabled);
	/**
	 * returns if the planet is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;

	/**
	 * return the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * planet logic.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override = 0;
	/**
	 * renders the planet.
	 */
	virtual void Render(AppContext_ty_c appContext) override = 0;
	/**
	 * resizes the planet.
	 * calls the hover text to resize.
	 */
	virtual void Resize(Vector2 resolution, AppContext_ty_c appContext) override = 0;
};
