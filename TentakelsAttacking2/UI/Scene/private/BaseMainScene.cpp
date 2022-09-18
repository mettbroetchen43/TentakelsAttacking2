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

    auto btnLeft = std::make_shared<ClassicButton>(
        1,
        GetElementPosition(0.15f, 0.025f),
        GetElementSize(0.2f, 0.1f),
        Alignment::TOP_MID,
        uiManager.GetResolution(),
        "Super Testtext, viel besser Text",
        appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        SoundType::CLICKED_RELEASE_STD);
    m_elements.push_back(btnLeft);

    auto btnMid = std::make_shared<ClassicButton>(
        2,
        GetElementPosition(0.4f, 0.025f),
        GetElementSize(0.2f, 0.1f),
        Alignment::TOP_MID,
        uiManager.GetResolution(),
        "Quit",
        appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        SoundType::CLICKED_RELEASE_STD);
    m_elements.push_back(btnMid);

    auto btnRight = std::make_shared<ClassicButton>(
        3,
        GetElementPosition(0.65f, 0.025f),
        GetElementSize(0.2f, 0.1f),
        Alignment::TOP_MID,
        uiManager.GetResolution(),
        "Super Testtext, viel besser Text",
        appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        SoundType::CLICKED_RELEASE_STD);
    m_elements.push_back(btnRight);
}