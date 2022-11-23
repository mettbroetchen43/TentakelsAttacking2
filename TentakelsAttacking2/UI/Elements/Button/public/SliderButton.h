//
// Purpur Tentakel
// 31.08.2022
//

#pragma once
#include "Button.h"

/**
 * is used by the sliderclass as button to slide.
 */
class SliderButton final : public Button {
public:
	using Button::Button;
	using Button::operator=;

	/**
	 * logic of the slider button.
	 * calls ChackAndUpdate from button.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;

};