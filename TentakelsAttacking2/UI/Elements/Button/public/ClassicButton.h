//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "Button.h"
#include "Focusable.h"

class ClassicButton : public Button, public Focusable {
private:
public:
	ClassicButton(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		Vector2 resolution, std::string const& text, Texture2D* texture, SoundType releaseSound);
	ClassicButton(ClassicButton const&) = default;
	ClassicButton(ClassicButton&& old) = default;
	ClassicButton& operator= (ClassicButton const&) = default;
	ClassicButton& operator= (ClassicButton&&) = default;
	~ClassicButton() = default;

	[[nodiscard]] bool IsEnabled() const override;

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	[[nodiscard]] Rectangle GetCollider() const override;
};