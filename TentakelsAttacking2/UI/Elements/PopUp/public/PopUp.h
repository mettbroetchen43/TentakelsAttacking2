//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <vector>
#include <memory>


class PopUp : public UIElement {
protected:
	bool m_firstEnter = false;
	std::vector<std::shared_ptr<UIElement>> m_elements;
	Rectangle m_colider;

	void Initialize(std::string const& title, std::string& subTitle,
		AssetType infoTexture, Vector2 resolution);
	void LateUpdate();

	Rectangle GetColiderWithMaxValues(Texture2D* texture, float maxWidth, float maxHeight) const;

	void UpdateColider(Vector2 resolution) override;

public:
	PopUp(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, 
		std::string const& title, std::string& subTitle, AssetType infoTexture);
	virtual ~PopUp() = default;

	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	virtual void Render(AppContext const& appContext) override;
	virtual void Resize(Vector2 resolution, AppContext const& appContext) override;
};
