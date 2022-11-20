//
// Purpur Tentakel
// 29.08.2022
//

#pragma once
#include "SliderButton.h"

class Slider final : public UIElement {
private:
	bool m_isEnabled = true;
	bool m_isHorizontal;
	bool m_isPressed = false;
	bool m_isScroll = false;
	float m_absoluteDimension = 1.0f;
	float m_btnOffset = 0.0f;
	Texture2D* m_texture;
	Rectangle m_textureRec;

	SliderButton m_btn;
	std::function<void(float)> m_onSlide =[](float) {};

	void CalculateInitialButton();

	void CalculateOnSlide() const;
	void Slide();
	void SlideIfPressed();
	void MoveButtonIfColiderIsPressed(Vector2 const& mousePosition);
	void SlideIfScroll();
	void SetOffset(Vector2 mousePosition);

public:
	Slider(Vector2 pos,Vector2 size, Alignment alignment, Vector2 resolution,
		bool isHorizontal, float absoluteDimension);
	Slider(Slider const&) = default;
	Slider(Slider&&) = default;
	Slider& operator=(Slider const&) = default;
	Slider& operator= (Slider&&) = default;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
 
	void SetOnSlide(std::function<void(float)> onSlide);
	void SetButtonPosition(float position);

	void SetScrolling(bool isScroll);
	[[nodiscard]] bool IsScrolling() const;

	void SetAboluteDimension(float absolutDimension);
	[[nodiscard]] float GetAbsoluteDimension() const;

	void SetEnabled(bool isEnabled);
};
