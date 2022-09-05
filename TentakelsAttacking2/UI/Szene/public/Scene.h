//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "UIElement.h"
#include <vector>
#include <memory>

class Focus;
class UIManager;

class Scene: public UIElement {
protected:
	std::vector<std::shared_ptr<UIElement>> m_elements;
	bool m_active;

	virtual void InitializeSzene(UIManager const& uiManager) = 0;
	void SetFocusActive(Focus& focus);

public:
	Scene(Vector2 size, Vector2 pos, bool active);
	Scene(Scene const&) = default;
	Scene(Scene&&) = default;
	Scene& operator= (Scene const&) = default;
	Scene& operator= (Scene&&) = default;
	~Scene() = default;

	[[nodiscard]] bool IsActive() const;
	void SetActive(bool active, Focus& focus);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render() override;
	void Resize(Vector2 resolution) override;
};
