//
// Purpur Tentakel
// 08.08.2022
// C++ 20
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "UIManager.h"
#include "Button.h"
#include <vector>
#include <iostream>

void test() {
    std::cout << "clicked" << '\n';
    // exit(0);
}

int main() {
    UIManager uiManager;

    auto ptr = std::make_shared<Button>("Assets/btn_f_default.png", Vector2(0.6f, 0.2f), Vector2(0.2f, 0.13f), uiManager.GetResolution(), "Super Testtext, viel besser Text", SoundType::ACCEPTED, test);
    uiManager.AddElement(ptr);
    ptr = std::make_shared<Button>("Assets/btn_f_default.png", Vector2(0.4f, 0.4f), Vector2(0.3f, 0.2f), uiManager.GetResolution(), "Quit",SoundType::CLICKED_RELEASE_STD, test);
    ptr->SetEnabled(false);
    uiManager.AddElement(ptr);

    uiManager.UILoop();

    return 0;
}