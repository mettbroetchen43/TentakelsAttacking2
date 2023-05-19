//
// Purpur Tentakel
// 14.09.2022
//

#include "Logos.h"
#include "SceneType.h"
#include "AppContext.h"
#include "UIManager.h"
#include "Text.h"
#include "Picture.h"
#include "HInput.h"
#include <memory>


void LogoScene::Initialize() {
	auto logo = std::make_shared<Picture>(
		GetElementPosition(0.5f, 0.1f),
		GetElementSize(0.0f, 0.5f),
		Alignment::TOP_MID,
		m_resolution,
		AssetType::LOGO
		);
	m_elements.push_back(logo);

	auto mainText = std::make_shared<Text>(
		GetElementPosition(0.5f, 0.65f),
		GetElementSize(1.0f, 0.1f),
		Alignment::TOP_MID,
		m_resolution,
		Alignment::TOP_MID,
		0.07f,
		"A Purpur Tentakel production"
		);
	//mainText->RenderRectangle(true);
	m_elements.push_back(mainText);

	auto skipText = std::make_shared<Text>(
		GetElementPosition(0.99f, 0.97f),
		GetElementSize(0.2f, 0.03f),
		Alignment::BOTTOM_RIGHT,
		m_resolution,
		Alignment::BOTTOM_RIGHT,
		0.03f,
		"skip with [ESC]"
		);
	// skipText->RenderRectangle(true);
	m_elements.push_back(skipText);
}

LogoScene::LogoScene(Vector2 resolution)
	:Scene{ {0.0f, 0.0f}, {1.0f, 1.0f}, Alignment::DEFAULT, resolution },
	m_time{ GetTime() } {
	Initialize();
}
void LogoScene::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {
	bool const nextScene{
			IsBackInputPressed()
		or (m_time + SCENE_LENGTH) < GetTime() 
	};
	if (nextScene) {
		SwitchSceneEvent event{ m_nextScene };
		appContext.eventManager.InvokeEvent(event);
	}

	for (auto e : m_elements) {
		e->CheckAndUpdate(mousePosition, appContext);
	}
}
void LogoScene::Render(AppContext const& appContext) {
	for (auto e : m_elements) {
		e->Render(appContext);
	}
}
void LogoScene::Resize(Vector2 resolution, AppContext const& appContext){
	for (auto e : m_elements) {
		e->Resize(resolution, appContext);
	}
}
