//
// Purpur Tentakel
// 16.06.2023
//

#pragma once
#include "UIElement.hpp"
#include "Line.h"
#include "HPlayerCollection.h"
#include "HLogicAlias.hpp"
#include "Hover.h"

class UIFleet final : public UIElement {
private:
	PlayerData m_player; ///< contains the current player data
	Fleet_ty_raw_c m_fleet; ///< contains the logic Planet to this Planet
	Line m_line; ///< contains the line for displaying
	Hover m_hover; ///< contains the hover Element
	Vector2 m_relativeStart; ///< contains teh relative start of the line according to the galaxy
	Vector2 m_relativeEnd; ///< contains teh relative end of the line according to the galaxy
	std::function<bool(Vector2 const&)> m_isInGalaxyCollider; ///< returns if a point is in the galaxy collider

public:
	UIFleet(PlayerData player, Vector2 start, Vector2 end, Vector2 resolution, Vector2 relativeStart, Vector2 relativeEnd,
		Fleet_ty_raw_c fleet, std::function<bool(Vector2 const&)> isInGalaxyCollider);
	
	/**
	 * checks if a point is colliding with the line.
	 */
	[[nodiscard]] bool IsColliding(Vector2 const& mousePosition) const;

	/**
	 * updates the hover text.
	 */
	void UpdateHoverText();

	/**
	 * updates the start and end positions
	 */
	void UpdatePositions(Rectangle newCollider);

	/**
	 * calls the UIElement to Update.
	 * checks collision with line.
	 */
	virtual void CheckAndUpdate(Vector2 const&, AppContext_ty_c appContext);
	/**
	 * renders the line.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * calls UIElement to Resize.
	 * Resizes the line.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
