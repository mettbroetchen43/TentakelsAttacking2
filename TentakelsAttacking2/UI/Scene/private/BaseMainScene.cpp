//
// Purpur Tentakel
// 06.09.2022
//

#include "BaseMainScene.h"
#include "AppContext.h"
#include "UIManager.h"
#include "ClassicButton.h"

void BaseMainScene::InitializeSzene(UIManager const& uiManager) {
	AppContext& appContext = AppContext::GetInstance();

    auto ptr = std::make_shared<ClassicButton>(1, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        GetElementPosition(0.15f, 0.025f), GetElementSize(0.2f, 0.1f), uiManager.GetResolution(),
        "Super Testtext, viel besser Text", SoundType::ACCEPTED);
    //ptr->SetOnClick(test);
    m_elements.push_back(ptr);

    ptr = std::make_shared<ClassicButton>(2, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        GetElementPosition(0.4f, 0.025f), GetElementSize(0.2f, 0.1f), uiManager.GetResolution(),
        "Quit", SoundType::CLICKED_RELEASE_STD);
    //ptr->SetOnClick(test);
    m_elements.push_back(ptr);

    ptr = std::make_shared<ClassicButton>(3, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        GetElementPosition(0.65f, 0.025f), GetElementSize(0.2f, 0.1f), uiManager.GetResolution(),
        "Super Testtext, viel besser Text", SoundType::CLICKED_RELEASE_STD);
    //ptr->SetOnClick(test);
    m_elements.push_back(ptr);
}