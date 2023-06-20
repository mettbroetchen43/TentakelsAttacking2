//
// Purpur Tentakel
// 01.11.2022
//

#pragma once
#include "Scene.h"

class SliderAndInputLine;

/**
 * provides a scenes, where the global settings can be set.
 */
class SettingsScene final : public Scene {
private:
	using DropDownButton_ty = std::pair<ClassicButton_ty, bool>;
	std::shared_ptr<SliderAndInputLine> m_volume; ///< contains the volume slider
	std::vector<std::pair<Resolution, std::string>> m_rawResolutionEntries; ///< contains die raw resolution information
	std::pair<DropDownButton_ty, DropDownButton_ty> m_resolutionDropDownBtn; ///< contains the two buttons that are hidden by the resolution drop down
	
	DropDown_ty m_resolutionDropDown{ nullptr }; ///< contains the resoltuion drop down
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize(SceneType continueScene);

	/**
	 * returns the strings out of the raw resolution data.
	 */
	std::vector<std::string> GetStringsFromResolutionEntries() const;
	/**
	 * returns index from resolution enum.
	 */
	int GetIndexFromResolution(Resolution resolution) const;

public:
	/**
	 * ctor.
	 * only initialization.
	 */
	SettingsScene(Vector2 resolution, SceneType continueScene);

	/**
	 * updates all elements in elements.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders all elements in elements and elements out update.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes all elements in elements and elements out update.
	 */
	void Resize(Vector2 resolution, AppContext_ty_c appContext) override;
};
