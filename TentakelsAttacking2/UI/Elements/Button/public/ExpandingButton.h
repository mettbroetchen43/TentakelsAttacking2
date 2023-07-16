//
// Purpur Tentakel
// 16.07.2023
//

#pragma once
#include "HUIAlias.hpp"
#include "UIElement.hpp"

class ExpandingButton : public UIElement {
private:
	bool m_isExpanded{ false }; ///< contains if the button is currently expanded
	float m_spacing; ///< contains the relative spacing between the buttons
	ToggleButton_ty m_mainButton; ///< contains the toggle button
	std::vector<ClassicButton_ty> m_buttons; ///< contains the classic buttons

	/**
	 * calls collapse or expand.
	 */
	void HandleExpandChance(bool expanding);
	/**
	 * handles the expand if the expanded button.
	 */
	void HandleExpand();
	/**
	 * handles the collapse of the expanded button
	 */
	void HandleCollapse();

public:

	/**
	 */
	void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override;
	/**
	 * calls main button and button vector to render.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * calls main button and button vector to resize.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c) override;
};