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
	Vector2 m_coliderPos;
	Color m_color;
	std::function<void(UIPlanet*)> m_onClick = [](UIPlanet*) {};

public:
	UIPlanet(unsigned int focusID, unsigned int ID, Vector2 pos, Vector2 resolution, 
		Color color, Vector2 coliderPos);

	void UpdatePosition(Rectangle newColider);

	void SetOnClick(std::function<void(UIPlanet*)> onClick);

	void SetColor(Color color);
	[[nodiscard]] Color GetColor() const;

	[[nodiscard]] unsigned int GetID() const;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;

	[[nodiscard]] bool IsEnabled() const override;
	void SetEnabled(bool isEnabled);

	[[nodiscard]] Rectangle GetCollider() const override;
};
