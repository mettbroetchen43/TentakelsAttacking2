//
// Purpur Tentakel
// 12.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "EventListener.hpp"
#include "Focusable.h"

class UIGalaxy : public UIElement, public EventListener, public Focusable {
private:
	bool m_isEnabled = true;
	Rectangle m_colider;
	Rectangle m_absoluteSize;

public:
	UIGalaxy(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution);


	void UpdateColider(Vector2 resolution) override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	void SetEnabled(bool isEnabled);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void OnEvent(Event const& event) override;
};