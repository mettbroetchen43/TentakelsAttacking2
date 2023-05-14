//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include "Text.h"
#include "HPlayerData.hpp"
#include "Hover.h"
#include <functional>
#include <memory>

/**
 * provieds a Ui representaition if the logic Planet.
 * gets implemented by the UIGalaxy.
 */
class UIPlanet final : public UIElement, public Focusable {
private:
	unsigned int m_ID; ///< contains the unique planet ID with is also the planet "name"
	std::string m_stringID; ///< contains the ID as string
	bool m_isEnabled = true; ///< contains if the element is enabled
	Vector2 m_coliderPos; ///< the position of the colider
	PlayerData m_currentPlayer; ///< contains the current player data that own the planet
	Color m_color; ///< contains the current color -> match the player color
	std::function<void(UIPlanet*)> m_onClick = [](UIPlanet*) {}; ///< contains on click that gets called when the planet is clicked
	Hover m_hover; ///< contains the hover element
	bool m_renderHover = false; ///< contains if the hover text should be rendered


public:
	/**
	 * ctor.
	 * converts the id to a string.
	 */
	UIPlanet(unsigned int focusID, unsigned int ID, PlayerData player, Vector2 pos, Vector2 resolution, 
		Vector2 coliderPos);

	/**
	 * Updates the position with the colider position.
	 */
	void UpdatePosition(Rectangle newColider);

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
	 * sets the current color if it schould not match the playercolor.
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
	 * planet logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the planet.
	 */
	void Render(AppContext const& appContext) override;
	/**
	/**
	 * resizes the planet.
	 * calls the hover text to resize.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;

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
};
