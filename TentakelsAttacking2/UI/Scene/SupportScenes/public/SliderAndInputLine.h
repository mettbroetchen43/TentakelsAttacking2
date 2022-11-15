//
// Purpur Tentakel
// 27.10.2022
//

#pragma once
#include "Scene.h"
#include "InputLine.hpp"
#include <functional>

class Slider;
class ClassicButton;

class SliderAndInputLine : public Scene {
private:
	std::shared_ptr<Slider> m_slider;
	std::shared_ptr<InputLine<int>> m_inputLine;
	std::shared_ptr<ClassicButton> m_btn;
	std::function<void(int)> m_onSave = [](int) {};

	bool m_isEnabled = true;
	bool m_slided = false;
	int m_minValue, m_maxValue, m_currentValue;

	void Initialize(unsigned int focusID, Vector2 resolution);
	void BtnPressed();
	void SaveValue();
	void Slide(float position);
	void ValidateCurrentValue();
	void SetSliderValue() const;

public:
	SliderAndInputLine(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		int minValue, int maxValue, int currentValue, Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;

	void SetEnabled(bool isEnabled);

	void SetOnSave(std::function<void(int)> onSave);
	void SetValue(int value);

	void RandomValue();
};
