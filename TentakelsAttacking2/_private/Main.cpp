//
// Purpur Tentakel
// 08.08.2022
// C++ 20
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "AppContext.h"
#include "UIManager.h"
#include "Slider.h"
#include <vector>
#include <iostream>

void test() {
    std::cout << "clicked" << '\n';
    // exit(0);
}

int main() {
    AppContext appContext;
    appContext.eventManager.AddListener(&appContext.soundManager);
    UIManager uiManager(appContext);

    auto ptr = std::make_shared<Button>(appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        Vector2(0.6f, 0.2f), Vector2(0.2f, 0.13f), uiManager.GetResolution(),
        "Super Testtext, viel besser Text", SoundType::ACCEPTED);
    ptr->SetOnClick(test);
    uiManager.AddElement(ptr);
    ptr = std::make_shared<Button>(appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT),
        Vector2(0.4f, 0.4f), Vector2(0.3f, 0.2f), uiManager.GetResolution(),
        "Quit",SoundType::CLICKED_RELEASE_STD);
    ptr->SetEnabled(false);
    ptr->SetOnClick(test);
    uiManager.AddElement(ptr);
    auto ptr2 = std::make_shared<Slider>(appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        Vector2(0.1f, 0.1f), Vector2(0.025f, 0.7f), uiManager.GetResolution(),
        6.0f, false, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT));
    uiManager.AddElement(ptr2);
    ptr2 = std::make_shared<Slider>(appContext.assetManager.GetTexture(AssetType::GREY_SQUARE),
        Vector2(0.1f, 0.85f), Vector2(0.7f, 0.025f), uiManager.GetResolution(),
        6.0f, true, appContext.assetManager.GetTexture(AssetType::BUTTON_DEFAULT));
    uiManager.AddElement(ptr2);

    uiManager.UILoop();

    return 0;
}