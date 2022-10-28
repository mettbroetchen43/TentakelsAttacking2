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
	auto& constants = AppContext::GetInstance().constants;
	std::ofstream file;

	file.open(constants.files.config);
	if (!file.is_open()) {
		std::cout << "Cant Open Config\n";
		return;
	}

	auto headline = [](std::string const& headline, std::string& toSave) {
		toSave += "//\n// " + headline + '\n';
	};
	auto entry = [](std::string const& entry, std::string const& message, std::string& toSave) {
		toSave += entry + " - " + message + "\n";
	};
	std::string toSave = "//\n// Purpur Tentakel\n// Tentakels Attacking\n// Config\n//\n";

	headline("Globals", toSave);
	entry(std::to_string(constants.global.startingModeFullScreen), "Starting Full Screen", toSave);

	headline("Player", toSave);
	entry(std::to_string(constants.player.minPlayerCount), "Min Player Count", toSave);
	entry(std::to_string(constants.player.maxPlayerCount), "Max Player Count", toSave);

	file << toSave;
	file.close();
}
