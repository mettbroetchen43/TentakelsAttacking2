//
// Purpur Tentakel
// 27.10.2022
//

#include "ConfigIO.h"
#include "AppContext.h"
#include <fstream>
#include <filesystem>
#include <iostream>

static constexpr char token = '-';

void LoadConfig() {

}

void SaveConfig() {
	AppContext& appContext = AppContext::GetInstance();
	std::ofstream file;

	file.open(appContext.constants.files.config);
	if (!file.is_open()) {
		std::cout << "Cant Open Config\n";
		return;
	}

	std::string toSave = "//\n// Purpur Tentakel\n// Tentakels Attacking\n// Config\n//\n//\n";

	toSave += "// Globals\n";
	toSave += std::to_string(appContext.constants.global.startingModeFullScreen) + " - Starting Full Screen";

	file << toSave;
	file.close();
}
