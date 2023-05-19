//
// Purpur Tentakel
// 04.11.2022
//

#pragma once
#include "Scene.h"

class Title;
class ClassicButton;
class Line;

/**
 * provides the credits scene.
 */
class CreditsScene final : public Scene {
private:
	std::shared_ptr<Title> m_title; ///< contains the title
	std::shared_ptr<Line> m_titleLine; ///< contains the line below title
	std::shared_ptr<ClassicButton> m_finishBTN;  ///< contains the button that gets displayed at the end of the credits
	std::shared_ptr<ClassicButton> m_speedBTN; ///< contains the button that can toggle the credit speed
	float m_speed{ 0.07f }; ///< contains the base credit speed -> speed level 1
	int m_maxSpeedLevel{ 3 }; ///< contains the maximum speed level.
	int m_speedLevel{ 1 }; ///< contains the current speed level.
	std::vector<std::shared_ptr<UIElement>> m_movingElements; ///< contains the elements that are moving during the credits

	/**
	 * initializes all ui elements.
	 * contains all the text.
	 * connects the actions.
	 */
	void Initialize(Vector2 resolution);
	/**
	 * adds an element ass moving element an into the normal elements.
	 */
	void AddMovingElement(std::shared_ptr<UIElement> element);

	/**
	 * increases the speed level by one.
	 * resets to 1 once the max speed level gets crossed.
	 */
	void ToggleSpeedLevel();
	/**
	 * moves the credits.
	 * returns if the credits currently are not moving.
	 * moves all elements in moving elements.
	 */
	void Move();
	/**
	 * checks if the credits are finished.
	 * sets moving to false if so.
	 */
	void CheckCreditsFinished();

public:
	/**
	 * ctor
	 * only initialization.
	 */
	CreditsScene(Vector2 resolution);

	/**
	 * sets moving to true when the title is fully animated.
	 * calls the moving elements to move as long as moving is true.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * sets the new resolution.
	 * calls all elements zu resize.
	 */
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
