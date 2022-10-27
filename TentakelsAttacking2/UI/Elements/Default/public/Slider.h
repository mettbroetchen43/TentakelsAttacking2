//
// Purpur Tentakel
// 29.08.2022
//

#pragma once
#include "SliderButton.h"

class Slider: public UIElement {
private:
	bool m_isHorizontal;
	bool m_isPressed = false;
	Texture2D* m_texture;
	Rectangle m_textureRec;
	Rectangle m_collider;

	SliderButton m_btn;

	void CalculateInitialButton(Vector2 resolution, float absolutDimension);

	void Slide();
	void SlideIfPressed();
	void MoveButtonIfColiderIsPressed(Vector2 const& mousePosition);

public:
	Slider(Vector2 pos,Vector2 size, Alignment alignment, bool isHorizontal, 
		float absoluteDimension, Vector2 resolution);
	Slider(Slider const&) = default;
	Slider(Slider&&) = default;
	Slider& operator=(Slider const&) = default;
	Slider& operator= (Slider&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};
