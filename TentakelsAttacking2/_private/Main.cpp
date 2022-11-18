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

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(100, 100, "");
	AppContext& appContext = AppContext::GetInstance();

	UIManager uiManager;
	SetWindowTitle(("Tentakels Attacking " + appContext.constants.global.version).c_str());

	appContext.LoadConfig();

	uiManager.StartUI();

	appContext.SaveConfig();

	return 0;
}