//
// Purpur Tentakel
// 31.08.2022
//

#pragma once
#include "Button.h"

class SliderButton : public Button {
public:
	using Button::Button;
	using Button::operator=;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;

};