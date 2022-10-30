//
// Purpur Tentakel
// 27.10.2022
//

#include "ConfigIO.h"
#include "AppContext.h"
#include "HPrint.h"
#include <fstream>
#include <filesystem>
#include <vector>

static constexpr char token = '/';

void LoadConfig() {
	auto& constants = AppContext::GetInstance().constants;
	std::ifstream file;

	if (!std::filesystem::exists(constants.files.config)) {
		Print("config does not exists", PrintType::EXPECTED_ERROR);
		SaveConfig();
		return;
	}

	file.open(constants.files.config);
	if (!file.is_open()) {
		Print("cant open config");
		return;
	}

	auto nextEntry = [](std::ifstream& file, std::string& input) {
		while (std::getline(file, input)) {
			if (input.empty()) { continue; }
			if (input[0] == token) { continue; }

			size_t index = input.find_first_of(token);
			input = input.substr(0, index);
			return true;
		}
		return false;
	};

	auto addBools = [](std::vector<bool*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				*e = static_cast<bool>(std::stoi(input));
			}
		}
	};
	auto addSize_t = [](std::vector<size_t*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				int i = std::stoi(input);
				if (i < 0) {
					i = 0;
				}
				*e = i;
			}
		}
	};
	auto addFloat = [](std::vector<float*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				*e = std::stof(input);
			}
		}
	};
	std::string input;
	std::vector<bool*> boolEntries = {
		// Globals
		&constants.global.startingModeFullScreen,
	};
	addBools(boolEntries, file, input, nextEntry);

	std::vector<size_t*> size_tEntries = {
		// Player
		&constants.player.minPlayerCount,
		&constants.player.maxPlayerCount,
		// World
		&constants.world.minPlanetCount,
		&constants.world.maxPlanetCount,

		&constants.world.minDiemnsionX,
		&constants.world.maxDiemnsionX,
		&constants.world.minDiemnsionY,
		&constants.world.maxDiemnsionY
	};
	addSize_t(size_tEntries, file, input, nextEntry);

	std::vector<float*> floatEltries = {
		// Sound
		&constants.sound.masterVolume
	};
	addFloat(floatEltries, file, input, nextEntry);

	file.close();

#ifdef _DEBUG
	constants.global.startingModeFullScreen = false;
#endif // _DEBUG

	Print("config loaded");
}
void SaveConfig() {
	auto& constants = AppContext::GetInstance().constants;
	std::ofstream file;

	if (!std::filesystem::exists(constants.files.config)) {
		Print("generate config");
	}

	file.open(constants.files.config);

	std::string toSave = "//\n// Purpur Tentakel\n// Tentakels Attacking\n// Config\n//\n\n// Min Count >= 0\n";


	auto headline = [](std::string const& headline, std::string& toSave) {
		toSave += "\n// " + headline + '\n';
	};
	auto entry = [](std::string const& entry, std::string const& message, std::string& toSave) {
		toSave += entry + ' ' + token + ' ' + message + "\n";
	};

	headline("Globals", toSave);
	entry(std::to_string(constants.global.startingModeFullScreen), "Starting Full Screen (0 = window)", toSave);

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
	entry(std::to_string(constants.sound.masterVolume), "Master Volume (0.0 - 100.0)", toSave);

	file << toSave;
	file.close();

	Print("config saved");
}
