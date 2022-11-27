//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

/**
 * provieds a Ui representaition if the logic Planet.
 * gets implemented by the UIGalaxy.
 */
class UIPlanet final : public UIElement, public Focusable {
private:
	unsigned int m_ID; ///< contains the unique planet ID with is also the planet "name"
	std::string m_stringID; ///< contains the id as string so it dont gets castet every tick.
	bool m_isEnabled = true; ///< contains if the element is enabled
	Vector2 m_coliderPos; ///< the position of the colider
	Color m_color; ///< contain the color in that the planet is renderd
	std::function<void(UIPlanet*)> m_onClick = [](UIPlanet*) {}; ///< contains on click that gets called when the planet is clicked

public:
	/**
	 * ctor.
	 * converts the id to a string.
	 */
	UIPlanet(unsigned int focusID, unsigned int ID, Vector2 pos, Vector2 resolution, 
		Color color, Vector2 coliderPos);

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
	 * sets a color in that the planet is renderd.
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
	 * planet logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the planet.
	 */
	void Render(AppContext const& appContext) override;


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
