//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <vector>
#include <memory>


/**
 * provides a basic popup class.
 * all other popups will hesitate from this.
 */
class PopUp : public UIElement {
protected:
	bool m_firstEnter = false; ///< contains if enter is down while the popup gets initialized
	bool m_schouldClose = false; ///< contans if the popup should close at the end of the tick
	std::vector<std::shared_ptr<UIElement>> m_elements;

	/**
	 * initialazes all zu elements.
	 */
	void Initialize(std::string const& title, std::string& subTitle,
		AssetType infoTexture, Vector2 resolution);
	/**
	 * checks if irst enter ist still down.
	 */
	void LateUpdate();

	/**
	 * calculates the colider of the picture so thats its in correct shape.
	 */
	Rectangle GetColiderWithMaxValues(Texture2D* texture, float maxWidth, float maxHeight) const;

public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	PopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, 
		std::string const& title, std::string& subTitle, AssetType infoTexture);
	/**
	 * virtual dtor.
	 */
	virtual ~PopUp() = default;

	/**
	 * popup logic.
	 * calls elements to update.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	/**
	 * renders the popup.
	 * calls the elememts to render.
	 */
	virtual void Render(AppContext const& appContext) override;
	/**
	 * resizes the popup.
	 * calls the elements to resize
	 */
	virtual void Resize(Vector2 resolution, AppContext const& appContext) override;
};
