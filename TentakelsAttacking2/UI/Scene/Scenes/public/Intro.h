//
// Purpur Tentakel
// 12.09.2022
//

#pragma once
#include "Scene.h"
#include "AppContext.h"
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <functional>

class ClassicButton;

class Intro : public Scene {
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
	std::shared_ptr<ClassicButton> m_btn = nullptr;
	Vector2 m_textPosition;
	float m_fontSize;
	size_t m_charCount = 0;
	size_t m_maxCharCount;
	bool m_titleFinish = false;
	bool m_btnMovmendFinish = false;
	size_t m_maxBtnPosition;
	SceneType m_nextScene;
	
	void Initialize(AppContext& appContext, UIManager const& uiManager);

	void RenderTitle(AppContext const& appContext);
	void RenderTitleSequens(AppContext const& appContext);

	void MeasureTitleLength();
	void ResizeText(AppContext const& appContext, Vector2 resolution);

	void TitleFinish(AppContext const& appContext);
	void MoveBtn();
	void BtnMoveFinish();

	void StartGame();

public:
	Intro(Vector2 pos, Vector2 size, Alignment alignment,
		UIManager const& uiManager, SceneType nextScene);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext) override;
	void SetActive(bool active, AppContext const& appContext) override;
};