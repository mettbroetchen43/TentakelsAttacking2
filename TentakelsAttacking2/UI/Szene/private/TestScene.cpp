//
// Purpur Tentakel
// 05.09.2022
//

#include "TestScene.h"
#include "Slider.h"
#include "AppContext.h"
#include "UIManager.h"

TestScene::TestScene(Vector2 pos, Vector2 size, bool active, UIManager const& uiManager)
    : BaseMainScene(pos, size, active) {
    InitializeSzene(uiManager);
}

void TestScene::InitializeSzene(UIManager const& uiManager) {
    AppContext& appContext = AppContext::GetInstance();

    BaseMainScene::InitializeSzene(uiManager);

    auto ptr2 = std::make_shared<Slider>(appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.05f, 0.1f), GetElementSize(0.025f, 0.75f), uiManager.GetResolution(),
        6.0f, false, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT));
    m_elements.push_back(ptr2);

    ptr2 = std::make_shared<Slider>(appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.05f, 0.9f), GetElementSize(0.9f, 0.025f), uiManager.GetResolution(),
        6.0f, true, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT));
    m_elements.push_back(ptr2);
}
