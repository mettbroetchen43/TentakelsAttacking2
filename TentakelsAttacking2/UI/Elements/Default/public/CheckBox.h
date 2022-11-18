//
// Purpur Tentakel
// 23.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

class CheckBox final : public UIElement, public Focusable {
private:
	bool m_isEnabled = true;
	bool m_isChecked = false;
	bool m_isHovered = false;

	unsigned int m_ID;

	Texture* m_texture;
	Rectangle m_textureRec;

	Texture* m_greyTexture;
	Rectangle m_greyTextureRec;

	std::function<void(unsigned int, bool)> m_onCheck = 
		[](unsigned int, bool) {};

	void Check(AppContext const& appContext);

public:
	CheckBox(unsigned int focusID, Vector2 pos, float height,
		Alignment alignment, Vector2 resolution, unsigned int checkBoxID);

	void SetOnCheck(std::function<void(unsigned int, bool)> onCheck);
	[[nodiscard]] unsigned int GetID() const;

	void SetChecked(bool isChecked);
	[[nodiscard]] bool IsChecked() const;

	void SetEnabled(bool isEnabled);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
};