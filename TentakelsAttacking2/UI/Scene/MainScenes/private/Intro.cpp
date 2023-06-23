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
#include "SceneType.h"
#include "HRandom.h"
#include "HInput.h"

void Intro::Initialize( ) {
	AppContext_ty appContext = AppContext::GetInstance();
	m_title = std::make_shared<Title>(
		GetElementPosition(0.5f, 0.1f),
		GetElementSize(0.9f, 0.3f),
		Alignment::TOP_MID,
		m_resolution,
		true,
		appContext
		);
	m_elements.push_back(m_title);

	m_btn = std::make_shared<ClassicButton>(
		1,
		GetElementPosition(0.5f, 1.1f),
		GetElementSize(0.3f, 0.2f),
		Alignment::MID_MID,
		m_resolution,
		appContext.languageManager.Text("scene_intro_start_btn"),
		SoundType::ACCEPTED
		);
	m_btn->SetEnabled(false);
	m_elements.push_back(m_btn);

	auto skipText = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.97f),
		GetElementSize(0.2f, 0.03f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.03f,
		appContext.languageManager.Text("scene_intro_skip", "[ESC]")
		);
	// skipText->RenderRectangle(true);
	m_elements.push_back(skipText);


	m_btn->SetOnClick([]() {
		AppContext::GetInstance().eventManager.InvokeEvent(SwitchSceneEvent(SceneType::MAIN_MENU));
	});
}

Intro::Intro(Vector2 resolution)
	:Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, Alignment::DEFAULT, resolution } {
	Initialize();
}

void Intro::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	m_title->CheckAndUpdate(mousePosition, appContext);

	bool const skipBtn{
			IsBackInputPressed()
		and m_title->HasFinishedTitle()
		and m_btn->IsMoving() 
	};
	if (skipBtn) {
		m_btn->StopMoving();
		m_btn->SetPosition({ 0.5f, 0.5f });
		return;
	}

	if (m_title->IsTitleFinished()) {
		m_btn->SetEnabled(true);
		m_btn->MoveToPositionAsymptotic(
			Vector2(0.5f, 0.5f),
			1.0f
		);
	}

	m_btn->CheckAndUpdate(mousePosition, appContext);
}
void Intro::Render(AppContext_ty_c appContext) {
	for (auto& e : m_elements) {
		e->Render(appContext);
	}
}
void Intro::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	for (auto& e : m_elements) {
		e->Resize(resolution, appContext);
	}
}

void Intro::SetActive(bool active, AppContext_ty_c appContext) {
	Scene::SetActive(active, appContext);
	SelectFocusElementEvent const event{ m_btn.get() };
	appContext.eventManager.InvokeEvent(event);
}
