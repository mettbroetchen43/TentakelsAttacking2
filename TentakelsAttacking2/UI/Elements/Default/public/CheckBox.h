//
// Purpur Tentakel
// 23.10.2022
//

#pragma once
#include "UIElement.hpp"
#include "Focusable.h"
#include <functional>

class CheckBox : public UIElement, public Focusable {
private:
	bool m_isEnabled = true;
	bool m_isChecked = false;
	bool m_isHovered = false;

	unsigned int m_ID;
	Rectangle m_colider;

	Texture* m_texture;
	Rectangle m_textureRec;

	Texture* m_greyTexture;
	Rectangle m_greyTextureRec;

	std::function<void(unsigned int, bool)> m_onCheck = 
		[](unsigned int, bool) {};

	void Check(AppContext const& appContext);

public:
	CheckBox(unsigned int focusID, Vector2 pos, Vector2 size,
		Alignment alignment, unsigned int checkBoxID,
		Vector2 resolution);

	void SetOnCheck(std::function<void(unsigned int, bool)> onCheck);

	void SetChecked(bool isChecked);
	[[nodiscard]] bool IsChecked() const;

	void SetEnabled(bool isEnabled);
	[[nodiscard]] bool IsEnabled() const override;
	[[nodiscard]] Rectangle GetCollider() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;
};