//
// Purpur Tentakel
// 12.09.2022
//

#pragma once
#include "Scene.h"
#include "AppContext.h"
#include "SceneType.h"
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <functional>

class ClassicButton;
class Title;

class Intro final : public Scene {
private:
	std::shared_ptr<Title> m_title = nullptr;
	std::shared_ptr<ClassicButton> m_btn = nullptr;
	bool m_btnMovmendFinish = false;
	float m_maxBtnPosition = 0.5f;
	SceneType m_nextScene = SceneType::MAIN_MENU;
	
	void Initialize(AppContext& appContext, Vector2 resolution);

	void MoveBtn();
	void BtnMoveFinish();

	void StartGame();

public:
	Intro(Vector2 resolution);

	void CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext);
	void Render(AppContext const& appContext);
	void Resize(Vector2 resolution, AppContext const& appContext) override;
	void SetActive(bool active, AppContext const& appContext) override;
};