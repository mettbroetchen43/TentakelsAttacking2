//
// Purpur Tentakel
// 21.11.2022
//

#pragma once
#include "PopUp.h"
#include <functional>

/**
 * provides a popup to validate.
 */
class ValidatePopUp : public PopUp {
private:
	std::function<void(bool)> m_callback{ [](bool) {} }; ///< contains a lambda that provides an bool

	/**
	 * initializes all ui elements.
	 */
	void Initialize();

	/**
	 * sets the should close bool.
	 */
	void Close();
public:
	/**
	 * ctor.
	 * only initialization.
	 */
	ValidatePopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		std::string const& title, std::string& subTitle, AssetType infoTexture, std::function<void(bool)> callback);

	/**
	 * popup logic.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
};
