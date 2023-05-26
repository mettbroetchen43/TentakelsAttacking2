//
// Purpur Tentakel
// 14.11.2022
//

#pragma once
#include "PopUp.h"

class ClassicButton;
class Slider;
class CheckBox;

/**
 * provides a popup that sets the sound level.
 */
class SoundLevelPopUp final : public PopUp {
private:
	std::shared_ptr<Slider> m_slider; ///< contains the slider to set the sound level
	std::shared_ptr<CheckBox> m_checkBox; ///< contains the checkbox to mute the sound
	std::shared_ptr<ClassicButton> m_acceptBtn; ///< contains the button to set the current value

	/**
	 * initializes all ui elements.
	 */
	void Initialize(Vector2 resolution);

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	SoundLevelPopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle);

	/**
	 * renders the popup.
	 * calls the slider, checkbox and button to render.
	 */
	void Render(AppContext_ty_c appContext) override;
};
