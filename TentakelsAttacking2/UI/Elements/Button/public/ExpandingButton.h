//
// Purpur Tentakel
// 16.07.2023
//

#pragma once
#include "HUIAlias.hpp"
#include "UIElement.hpp"

class ExpandingButton : public UIElement {
public:
	enum Direction {
		LEFT,
		DOWN,
		RIGHT,
		UP
	};

private:
	bool m_isExpanded{ false }; ///< contains if the button is currently expanded
	float m_spacing; ///< contains the relative spacing between the buttons
	ToggleButton_ty m_mainButton; ///< contains the toggle button
	std::vector<ClassicButton_ty> m_buttons{ }; ///< contains the classic buttons
	Direction m_direction; ///< contains the current expand direction

	/**
	 * initializes the main button.
	 */
	void Initialize(int focusID, std::string const& btnText);

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
	ExpandingButton(int focusID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		Direction direction, float spacing, std::string const& btnText);

	void Add(ClassicButton_ty btn);
	void Remove(ClassicButton_ty btn);
	void Remove(int ind);

	/**
	 * sets the current expand direction.
	 */
	void SetDirection(Direction direction);
	/**
	 * returns the current expand direction.
	 */
	[[nodiscard]] Direction GetDirection() const;

	/**
	 * updates the expand collider.
	 * call this after direction change and add or remove button.
	 */
	void Update();

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