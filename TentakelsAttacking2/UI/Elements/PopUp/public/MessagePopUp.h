//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "PopUp.h"
#include "ClassicButton.h"
#include <functional>

/**
 * provides a popup that shows a message
 */
class MessagePopUp final : public PopUp {
private:
	std::function<void()> m_callback = []() {}; ///< contains the callback lambda that gets called when the popup is closed

	/**
	 * initializes all ui elements.
	 */
	void Initialize(Vector2 resolution);

public:
	/**
	 * ctor
	 * only initialaziation.
	 */
	MessagePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture, std::function<void()> callback);

	/**
	 * popup logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition,
		AppContext const& appContext) override;
};