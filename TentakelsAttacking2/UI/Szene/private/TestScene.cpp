//
// Purpur Tentakel
// 05.09.2022
//

#include "TestScene.h"
#include "Slider.h"
#include "AppContext.h"
#include "UIManager.h"
#include "StringInputLine.h"
#include "IntInputLine.h"
#include "DoubleInputLine.h"
#include "Events.h"

TestScene::TestScene(Vector2 pos, Vector2 size, bool active, UIManager const& uiManager)
    : BaseMainScene(pos, size, active) {
    InitializeSzene(uiManager);
}

void TestScene::InitializeSzene(UIManager const& uiManager) {
    AppContext& appContext = AppContext::GetInstance();

    BaseMainScene::InitializeSzene(uiManager);
    // focus ID > 3!

    auto ptr4 = std::make_shared < DoubleInputLine>(
        6,
        appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.4f, 0.7f),
        GetElementSize(0.2f, 0.05f),
        10,
        uiManager.GetResolution()
        );
    m_elements.push_back(ptr4);

    auto ptr3 = std::make_shared < IntInputLine>(
        5,
        appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.4f, 0.6f),
        GetElementSize(0.2f, 0.05f),
        10,
        uiManager.GetResolution()
        );
    m_elements.push_back(ptr3);

    auto ptr = std::make_shared<StringInputLine>(
        4,
        appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.4f, 0.5f),
        GetElementSize(0.2f, 0.05f),
        40,
        uiManager.GetResolution()
        );
    m_elements.push_back(ptr);

    auto ptr2 = std::make_shared<Slider>(
        appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.05f, 0.1f),
        GetElementSize(0.025f, 0.75f),
        uiManager.GetResolution(),
        6.0f,
        false,
        appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT)
        );
    m_elements.push_back(ptr2);

    ptr2 = std::make_shared<Slider>(
        appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        GetElementPosition(0.05f, 0.9f),
        GetElementSize(0.9f, 0.025f),
        uiManager.GetResolution(),
        6.0f,
        true,
        appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT)
        );
    m_elements.push_back(ptr2);

    auto event = SelectFocusEvent(ptr.get());
    appContext.eventManager.InvokeEvent(event);
}
