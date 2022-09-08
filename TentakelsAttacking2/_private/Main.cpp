//
// Purpur Tentakel
// 08.08.2022
// C++ 20
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "AppContext.h"
#include "UIManager.h"
#include "Slider.h"
#include "ClassicButton.h"
#include <vector>
#include <iostream>

void test() {
    std::cout << "clicked" << '\n';
    // exit(0);
}

int main() {
    UIManager uiManager;
    [[maybe_unused]] AppContext& appContext = AppContext::GetInstance();

    uiManager.StartUI();

    return 0;
}