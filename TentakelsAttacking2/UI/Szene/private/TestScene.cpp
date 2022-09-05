//
// Purpur Tentakel
// 05.09.2022
//

#include "TestScene.h"
#include "ClassicButton.h"
#include "Slider.h"
#include "AppContext.h"
#include "UIManager.h"

TestScene::TestScene(Vector2 size, Vector2 pos, bool active, UIManager const& uiManager)
    : Scene(size, pos, active) {
    InitializeSzene(uiManager);
}

void TestScene::InitializeSzene(UIManager const& uiManager) {
    AppContext& appContext = AppContext::GetInstance();

    auto ptr = std::make_shared<ClassicButton>(1, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        Vector2(0.15f, 0.025f), Vector2(0.2f, 0.1f), uiManager.GetResolution(),
        "Super Testtext, viel besser Text", SoundType::ACCEPTED);
    //ptr->SetOnClick(test);
    m_elements.push_back(ptr);

    ptr = std::make_shared<ClassicButton>(2, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        Vector2(0.4f, 0.025f), Vector2(0.2f, 0.1f), uiManager.GetResolution(),
        "Quit", SoundType::CLICKED_RELEASE_STD);
    //ptr->SetOnClick(test);
    m_elements.push_back(ptr);

    ptr = std::make_shared<ClassicButton>(3, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        Vector2(0.65f, 0.025f), Vector2(0.2f, 0.1f), uiManager.GetResolution(),
        "Super Testtext, viel besser Text", SoundType::CLICKED_RELEASE_STD);
    //ptr->SetOnClick(test);
    m_elements.push_back(ptr);

    auto ptr2 = std::make_shared<Slider>(appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        Vector2(0.05f, 0.1f), Vector2(0.025f,0.75f), uiManager.GetResolution(),
        6.0f, false, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT));
    m_elements.push_back(ptr2);

    ptr2 = std::make_shared<Slider>(appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        Vector2(0.05f, 0.9f), Vector2(0.9f,0.025f), uiManager.GetResolution(),
        6.0f, true, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT));
    m_elements.push_back(ptr2);

}
