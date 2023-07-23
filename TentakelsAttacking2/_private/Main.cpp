//
// Purpur Tentakel
// 08.08.2022
// C++ 20
//

// original Random by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)

#include "HPrint.h"
#include "UIManager.h"
#include "HErrorLog.h"
#include "AppContext.h"
#include "HLogicAlias.hpp"

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(100, 100, "");
	AppContext_ty appContext{ AppContext::GetInstance() };
#ifdef _DEBUG
	Print(PrintType::BUILD, "Debug");
#else
	Print(PrintType::BUILD, "Release");
#endif // _DEBUG

	Print(PrintType::BUILD, appContext.constants.global.gameVersion);

	UIManager uiManager;

	appContext.LoadConfig();
	appContext.LoadLanguages();

	uiManager.StartUI();

	appContext.ValidateConfig();

	uiManager.StartUILoop();

	appContext.SaveConfig();

	CloseErrorStream();

	return 0;
}