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
	std::string toSave = "//\n// Purpur Tentakel\n// Tentakels Attacking\n// Config\n//\n";


	auto headline = [](std::string const& headline, std::string& toSave) {
		toSave += "//\n// " + headline + '\n';
	};
	auto entry = [](std::string const& entry, std::string const& message, std::string& toSave) {
		toSave += entry + " - " + message + "\n";
	};
	
	headline("Globals", toSave);
	entry(std::to_string(constants.global.startingModeFullScreen), "Starting Full Screen", toSave);

	headline("Player", toSave);
	entry(std::to_string(constants.player.minPlayerCount), "Min Player Count", toSave);
	entry(std::to_string(constants.player.maxPlayerCount), "Max Player Count", toSave);

	headline("World", toSave);
	entry(std::to_string(constants.world.minPlanetCount), "Min Planet Count", toSave);
	entry(std::to_string(constants.world.maxPlanetCount), "Max Planet Count", toSave);

	entry(std::to_string(constants.world.minDiemnsionX), "Min Dimension X", toSave);
	entry(std::to_string(constants.world.maxDiemnsionX), "Max Dimension X", toSave);
	entry(std::to_string(constants.world.minDiemnsionY), "Min Dimension Y", toSave);
	entry(std::to_string(constants.world.maxDiemnsionY), "Max Dimension Y", toSave);

	headline("Sound", toSave);
	
	file << toSave;
	file.close();
}
/*
size_t minPlanetCount = 20;
size_t maxPlanetCount = 100;

size_t minDiemnsionX = 40;
size_t minDiemnsionY = 20;
size_t maxDiemnsionX = 200;
size_t maxDiemnsionY = 160;
*/