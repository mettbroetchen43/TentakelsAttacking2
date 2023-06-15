//
// Purpur Tentakel
// 12.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "EventListener.hpp"
#include "Focusable.h"
#include "HLogicAlias.hpp"
#include <functional>
#include <memory>
#include <vector>

class UIPlanet;
class SendGalaxyPointerEvent;

/**
 * the representation of the logic galaxy.
 * can be shown as a show galaxy without interaction.
 */
class UIGalaxy final : public UIElement, public EventListener, public Focusable {
private:
	enum class Direction { ///< contains the possible directions that man on the arrow keys
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};
	bool m_isEnabled{ true }; ///< contains if the galaxy is enabled
	bool m_isScaling{ true }; ///< contains if the galaxy should be able to scale itself
	bool m_isScrollingByMouse{ false }; ///< contains if its currently scrolling by mouse wheel
	bool m_isShowGalaxy{ false }; ///< contains if the galaxy is only for show off
	float m_scaleFactor{ 1.0f }; ///< contains the scale factor of the galaxy
	Vector2 m_lastMousePosition{ 0.0f,0.0f }; ///< contains the position of the mouse from last tick while the galaxy is moved by mouse
	Rectangle m_absoluteSize; ///< contains the absolute size of the collider in px
	Galaxy_ty_raw m_currentGalaxy{ nullptr }; ///< contains a pointer of the current logic galaxy
	std::vector<UIGalaxyElement_ty> m_uiPlanets; ///< contains the UI planets that are generated from the logic galaxy
	std::function<void(float, Vector2)> m_onZoom{ [](float, Vector2) {} }; ///< contains onZoom -> gets called if the galaxy gets zoomed
	std::function<void(float, bool)> m_onSlide{ [](float, bool) {} }; ///< contains onSlide -> gets called if the galaxy gets slided
	std::function<void(unsigned int)> m_onUIGalaxyElementClick{ [](unsigned int) {} }; ///< contains onUIGalaxyElementClick -> gets called if a UIGalaxyElement gets clicked

	/**
	 * initializes all elements of the galaxy.
	 */
	void Initialize(SendGalaxyPointerEvent const* event);
	/**
	 * returns the absolute position if the provided pos in px.
	 */
	[[nodiscard]] Vector2 GetAbsolutePosition(Vector2 pos, AppContext_ty_c appContext) const;
	/**
	 * returns the relative position if the provided pos.
	 */
	[[nodiscard]] Vector2 GetRelativePosition(Vector2 pos, AppContext_ty_c appContext) const;

	/**
	 * returns if the provided planet is still inside of the galaxy collider
	 */
	[[nodiscard]] bool IsUIGalaxyElementInCollider(UIGalaxyElement_ty element) const;
	/**
	 * updates all button positions with the absolute size.
	 */
	void UpdateUIGalaxyElementPosition();
	/**
	 * calls onPlanetClick with the planet that gets provided.
	 */
	void SelectUIGalaxyElement(UIPlanet* planet);

	/**
	 * claps the absolute position and size so it gets never smaller that the collider.
	 */
	void ClampsPositionAndSize();
	/**
	 * calculates and calls onSlide for width and height.
	 */
	void PrepForOnSlide();
	/**
	 * moves the galaxy in the provided direction.
	 */
	void MoveByKey(Direction direction, float speed);
	/**
	 * checks if the mouse has moved since last tick.
	 * moved the galaxy in the same was.
	 */
	void MoveByMouse(Vector2 mousePosition);

	/**
	 * returns the current scale reference.
	 */
	[[nodiscard]] Vector2 GetCurrentScaleReference() const;

public:
	/**
	 * ctor.
	 * add an event listener.
	 * calls logic galaxy via event.
	 */
	UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution, bool isShowGalaxy = false);
	/**
	 * removed the event listener.
	 */
	~UIGalaxy();

	/**
	 * sets if the galaxy can be scaled.
	 */
	void SetIsScaling(bool isScaling);
	/**
	 * returns if the galaxy can be scaled.
	 */
	[[nodiscard]] bool IsScaling() const;

	/**
	 * returns the current scale factor of  the galaxy.
	 */
	[[nodiscard]] float GetScaleFactor() const;
	/**
	 * zooms the galaxy in or out.
	 * the factor defines how fast it is zooming.
	 * the galaxy is always zooming from the point if the mouse position if its inside the collider.
	 */
	void Zoom(bool zoomIn, int factor = 2);
	/**
	 * slides the galaxy to a certain position.
	 * needs zu be specified if its horizontal or vertical.
	 */
	void Slide(float position, bool isHorizontal);

	/**
	 * sets the onZoom lambda.
	 * gets called if the galaxy zooms or gets zoomed.
	 * contains the scale factor and the current scale reference.
	 */
	void SetOnZoom(std::function<void(float, Vector2)> onZoom);
	/**
	 * sets the onSlide lambda.
	 * gets called if the galaxy slides or gets slide.
	 * contains the position in percent and a bool is horizontal.
	 */
	void SetOnSlide(std::function<void(float, bool)> onSlide);
	/**
	 * sets the onPlanetClick lambda.
	 * gets called if a planet is clicked.
	 * contains the planet id.
	 */
	void SetOnUIGalaxyElementClick(std::function<void(unsigned int)> onPlanetClick);

	/**
	 * logic of the galaxy.
	 * calls the UIPlanets zu update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders the galaxy.
	 * calls the cells to render.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes the galaxy.
	 * calls the cells to resize.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;

	/**
	 * sets if the galaxy is enabled.
	 */
	void SetEnabled(bool isEnabled);
	/**
	 * returns if the galaxy is enabled.
	 */
	[[nodiscard]] bool IsEnabled() const override;
	/**
	 * returns the current collider.
	 */
	[[nodiscard]] Rectangle GetCollider() const override;

	/**
	 * returns the current galaxy.
	 */
	[[nodiscard]] Galaxy_ty_raw GetGalaxy() const;

	/**
	 * receives all events and calls the me,ber functions.
	 */
	void OnEvent(Event const& event) override;
};
