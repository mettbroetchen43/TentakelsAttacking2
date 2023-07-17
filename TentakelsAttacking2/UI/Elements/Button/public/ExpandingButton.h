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
	struct Btn {
		ClassicButton_ty btn;
		bool enabled;
		Vector2 pos;
	};

	bool m_isExpanded{ false }; ///< contains if the button is currently expanded
	bool m_wasKeyInput{ false }; ///< contains if the button got a key input last time
	float m_spacing; ///< contains the relative spacing between the buttons
	float m_expandingSpeed; ///< contains the speed the button is expanding and collapsing
	ToggleButton_ty m_mainButton; ///< contains the toggle button
	std::vector<Btn> m_buttons{ }; ///< contains the classic buttons
	Direction m_direction; ///< contains the current expand direction

	/**
	 * initializes the main button.
	 */
	void Initialize(int focusID, std::string const& btnText);

	/**
	 * calls collapse or expand.
	 */
	void HandleExpandChance(bool expanding, bool keyInput);
	/**
	 * handles the expand if the expanded button.
	 */
	void HandleExpand();
	/**
	 * handles the collapse of the expanded button
	 */
	void HandleCollapse();

	/**
	 * returns if any classic button is moving.
	 */
	[[nodiscard]] bool IsBtnMoving() const;

public:
	/**
	 * initializes the toggle button.
	 */
	ExpandingButton(int focusID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		Direction direction, float spacing, float expandigSpeed, std::string const& btnText);

	/**
	 * adds a new button.
	 * need to call update after that.
	 */
	void Add(ClassicButton_ty btn, bool enabled);
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
	 * updates the collider so it is over all buttons
	 */
	void UpdateCollider();

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