//
// Purpur Tentakel
// 09.11.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

class UIPlanet final : public UIElement, public Focusable {
private:
	unsigned int m_ID;
	std::string m_stringID;
	bool m_isEnabled = true;
	Rectangle m_colider;
	Vector2 m_coliderPos;
	Color m_color;
	std::function<void()> m_onClick = []() {};

public:
	UIPlanet(unsigned int focusID, unsigned int ID, Vector2 pos, Color color,
		Vector2 coliderPos, Vector2 resolution);

	void UpdatePosition(Rectangle newColider);

	void SetOnClick(std::function<void()> onClick);

	void UpdateColider(Vector2 resolution) override;

	void SetColor(Color color);
	[[nodiscard]] Color GetColor() const;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	[[nodiscard]] bool IsEnabled() const override;
	void SetEnabled(bool isEnabled);

	[[nodiscard]] Rectangle GetCollider() const override;
};
