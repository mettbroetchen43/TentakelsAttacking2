//
// Purpur Tentakel
// 14.09.2022
//

#include "Logos.h"
#include "SceneType.h"
#include "AppContext.h"
#include "AssetType.h"


LogoScene::LogoScene(Vector2 pos, Vector2 size,SceneType nextScene)
	:Scene(pos, size), m_nextScene(nextScene), m_time(GetTime()) {
	m_logo = AppContext::GetInstance().assetManager.GetTexture(AssetType::QUESTION_MARK);
}
void LogoScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {
	bool nextScene =
		IsKeyPressed(KEY_ESCAPE)
		or (m_time + SCENE_LENGTH) < GetTime();
	if (nextScene) {
		auto event = SwitchSceneEvent(m_nextScene);
		appContext.eventManager.InvokeEvent(event);
	}
}
void LogoScene::Render(AppContext const& appContext) {

}
void LogoScene::Resize(Vector2 resolution, AppContext const& appContext){

}

void LogoScene::SetActive(bool active, AppContext const& appContext) {
	Scene::SetActive(active, appContext);
}
