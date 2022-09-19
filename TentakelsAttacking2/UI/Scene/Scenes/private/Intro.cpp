//
// Purpur Tentakel
// 12.09.2022
//

#include "Intro.h"
#include "AppContext.h"
#include "UIManager.h"
#include "ClassicButton.h"
#include "Text.h"
#include "Title.h"
#include "AssetType.h"
#include "SoundType.h"
#include "SceneType.h"
#include "Events.h"
#include "random.h"


#define BTN_SPEED 2.5f

void Intro::Initialize(AppContext& appContext, UIManager const& uiManager) {
	m_title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.1f),
		GetElementSize(0.7f, 0.2f),
		Alignment::TOP_MID,
		32.0f,
		true,
		uiManager.GetResolution(),
		appContext
		);
	m_elements.push_back(m_title);

	m_btn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.5f, 1.1f),
		GetElementSize(0.3f, 0.2f),
		Alignment::MID_MID,
		uiManager.GetResolution(),
		"Start Game",
		appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
		SoundType::ACCEPTED
		);
	m_btn->SetEnabled(false);
	m_elements.push_back(m_btn);

	auto skipText = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.98f),
		GetElementSize(0.11f, 0.03f),
		Alignment::BOTTOM_RIGHT,
		0.03f,
		"skip with [ESC]",
		uiManager.GetResolution()
		);
	m_elements.push_back(skipText);


	std::function<void()> gameStart = [&]() {
		StartGame();
	};
	m_btn->SetOnClick(gameStart);
}

void Intro::MoveBtn() {
	auto colider = m_btn->GetCollider();
	if (colider.y - BTN_SPEED < m_maxBtnPosition) {
		BtnMoveFinish();
		return;
	}
	colider.y -= BTN_SPEED;
	m_btn->SetCollider(colider);
}
void Intro::BtnMoveFinish(){
	auto colider = m_btn->GetCollider();
	colider.y = static_cast<float>(m_maxBtnPosition);
	m_btn->SetCollider(colider);
	m_btnMovmendFinish = true;
	AppContext& appContext = AppContext::GetInstance();
	auto event = PlaySoundEvent(SoundType::ACCEPTED); // TODO
	appContext.eventManager.InvokeEvent(event);
}

void Intro::StartGame() {
	auto event = SwitchSceneEvent(m_nextScene);
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}

Intro::Intro(Vector2 pos, Vector2 size, Alignment alignment,
	UIManager const& uiManager, SceneType nextScene)
	:Scene(pos, size, alignment), m_nextScene(nextScene), m_maxBtnPosition(500) {

	AppContext& appContext = AppContext::GetInstance();
	Initialize(appContext, uiManager);
}

void Intro::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	m_title->CheckAndUpdate(mousePosition, appContext);

	if (m_title->IsTitleFinished()) {
		m_btn->SetEnabled(true);
		return;
	}

	bool skipBtn =
		IsKeyPressed(KEY_ESCAPE)
		and m_title->HasFinishedTitle()
		and !m_btnMovmendFinish;
	if (skipBtn) {
		BtnMoveFinish();
		return;
	}

	if (m_title->HasFinishedTitle() and !m_btnMovmendFinish) {
		MoveBtn();
	}
	m_btn->CheckAndUpdate(mousePosition, appContext);
}
void Intro::Render(AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Render(appContext);
	}
}
void Intro::Resize(Vector2 resolution, AppContext const& appContext) {
	for (auto& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}

void Intro::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
	auto event = SelectFocusElementEvent(m_btn.get());
	appContext.eventManager.InvokeEvent(event);
}
