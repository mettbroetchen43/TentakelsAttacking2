//
// Purpur Tentakel
// 29.08.2022
//

#pragma once
#include "Button.h"

class Slider: public UIElement {
private:
	bool m_isHorizontal;
	bool m_isPressed = false;
	Texture2D* m_texture;
	Rectangle m_textureRec;
	Rectangle m_collider;

	Button m_btn;

	Button CalculateInitialButton(Vector2 resolution, float absolutDimension, Texture2D* texture);

public:
	Slider(Texture2D* slideTexture, Vector2 pos, Vector2 size, Vector2 resolution,
		float absoluteDimension, bool isHorizontal, Texture2D* btnTexture);
	Slider(Slider const&) = default;
	Slider(Slider&&) = default;
	Slider& operator=(Slider const&) = default;
	Slider& operator= (Slider&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render() override;
	void Resize(Vector2 resolution) override;

	void Slide();
	void SlideIfPressed();
};
