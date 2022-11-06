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
	Texture2D* m_texture;
	Rectangle m_textureRec;
	Rectangle m_colider;

	SliderButton m_btn;
	std::function<void(float)> m_onSlide =[](float) {};

	void CalculateInitialButton(Vector2 resolution, float absolutDimension);

	void CalculateOnSlide() const;
	void Slide();
	void SlideIfPressed();
	void MoveButtonIfColiderIsPressed(Vector2 const& mousePosition);
	void SlideIfScroll();

	void UpdateColider(Vector2 resolution) override;

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

	void SetOnSlide(std::function<void(float)> onSlide);
	void SetButtonPosition(float position);

	void SetScrolling(bool isScroll);
	[[nodiscard]] bool IsScrolling() const;

	void SetEnabled(bool isEnabled);
};
