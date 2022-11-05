//
// Purpur Tentakel
// 04.11.2022
//

#pragma once
#include "Scene.h"

class Title;
class ClassicButton;

class CreditsScene : public Scene {
private:
	std::shared_ptr<Title> m_title;
	std::shared_ptr<ClassicButton> m_finishBTN;
	Vector2 m_resolution;
	bool m_moving = false;
	float m_speed = -0.002f;
	int m_maxSpeedLevel = 3;
	int m_speedLevel = 1;
	std::vector<std::shared_ptr<UIElement>> m_movingElements;

	void Initialize(Vector2 resolution);
	void AddMovingElement(std::shared_ptr<UIElement> element);

	void ToggleSpeedLevel();
	void Move();
	void CheckCreditsFinished();

public:
	CreditsScene(Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};