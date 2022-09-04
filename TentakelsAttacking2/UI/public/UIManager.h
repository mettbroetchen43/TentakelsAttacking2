//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "UIElement.h"
#include "AppContext.h"
#include "Focus.h"
#include <vector>
#include <memory>

class UIManager {
private:
	AppContext& m_appContext;
	Focus m_focus;
	std::vector<std::shared_ptr<UIElement>> m_elements;
	Vector2 m_resolution;

	void CheckAndUpdateResolution();
	void CheckAndUpdate();
	void Render();

public:
	UIManager();

	void UILoop();
	void AddElement(std::shared_ptr<UIElement> newElement);


	[[nodiscard]] Vector2 GetResolution() const;
};