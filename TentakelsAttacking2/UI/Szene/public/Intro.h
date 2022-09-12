//
// Purpur Tentakel
// 12.09.2022
//

#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <memory>

class ClassicButton;

class Intro : public Scene {
private:
	std::vector<std::string>* m_title;
	std::shared_ptr<ClassicButton> m_btn = nullptr;
	Vector2 m_textPosition;
	float m_fontSize;
	size_t m_charCount = 0;
	size_t m_maxCharCount;
	bool m_titleFinish = false;
	bool m_btnMovmendFinish = false;
	size_t m_maxBtnPosition;
	
	void RenderTitle(AppContext const& appContext);
	void RenderTitleSequens(AppContext const& appContext);

	void MeasureTitleLength();
	void ResizeText(AppContext const& appContext, Vector2 resolution);

	void SetBtnEnabled();
	void MoveBtn();

public:
	Intro(Vector2 pos, Vector2 size, bool active, UIManager const& uiManager);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution);
};