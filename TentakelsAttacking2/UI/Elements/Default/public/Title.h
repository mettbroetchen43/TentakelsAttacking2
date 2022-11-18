//
// Purpur Tentakel
// 19.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <array>
#include <vector>

class Title final : public UIElement {
private:
	std::array<std::string, 10> m_postFixes = {
	"  /-\\-",
	"  \\--/",
	"  -/--/",
	"  -\\_-\\",
	"  _/_\\",
	"  -_/\\-",
	"  --__-",
	"  __\\\\/",
	"  \\__-/",
	"  \\/-__",
	};
	std::vector<std::string>* m_title;
	float m_fontSize;
	size_t m_charCount = 0;
	size_t m_maxCharCount;
	bool m_titleFinish;
	bool m_lastFinishedTitle = false;
	static constexpr float ThirtyFife = 35.0f;

	void RenderTitle(AppContext const& appContext);
	void RenderTitleSequens(AppContext const& appContext);

	void MeasureTitleLength();
	void SetColider(AppContext const& appContext, Vector2 const& resolution);

	void TitleFinish(AppContext const& appContext);

public:
	Title(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
		bool drawTitle, AppContext& appContext);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) override;
	void Render(AppContext const& appContext) override;
	void Resize(Vector2 resolution, AppContext const& appContext) override;

	[[nodiscard]] bool HasFinishedTitle() const;
	[[nodiscard]] bool IsTitleFinished() const;
};