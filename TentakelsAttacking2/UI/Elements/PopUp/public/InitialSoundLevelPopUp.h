//
// Purpur Tentakel
// 14.11.2022
//

#pragma once
#include "PopUp.h"

class ClassicButton;
class SliderAndInputLine;
class CheckBox;

class InitialSoundLevelPopUp : public PopUp {
private:
	std::shared_ptr<SliderAndInputLine> m_slider;
	std::shared_ptr<CheckBox> m_checkBox;
	std::shared_ptr<ClassicButton> m_acceptBtn;

	void Initialize(Vector2 resolution);

public:
	InitialSoundLevelPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle);
};