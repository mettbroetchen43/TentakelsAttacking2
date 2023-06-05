//
// Purpur Tentakel
// 27.10.2022
//

#include "ConfigIO.h"
#include "AppContext.h"
#include "HPrint.h"
#include "HTextProcessing.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <optional>
#include <charconv>
#include <iomanip>

static constexpr char token{ '/' };

template<typename T>
std::optional<T> ParseNumber(std::string& input) {
	StripString(input);
	T value;
	auto const result{ std::from_chars(input.data(), input.data() + input.length(), value) };
	if (result.ec != std::errc() or result.ptr != input.data() + input.length()) {
		Print("not able to load config -> \"" + input + "\"", PrintType::ERROR);
		return {};
	}
	return value;
};

void LoadConfig() {
	auto& constants = AppContext::GetInstance().constants;
	std::ifstream file;

	if (!std::filesystem::exists(constants.files.configFile())) {
		Print("config does not exists", PrintType::EXPECTED_ERROR);
		SaveConfig();
		return;
	}

	file.open(constants.files.configFile());
	if (!file.is_open()) {
		Print("cant open config", PrintType::INFO);
		return;
	}

	auto nextEntry = [](std::ifstream& file, std::string& input) {
		while (std::getline(file, input)) {
			if (input.empty()) { continue; }
			if (input[0] == token) { continue; }

			size_t const index{ input.find_first_of(token) };
			input = input.substr(0, index);
			return true;
		}
		return false;
	};

	auto addBools = [](std::vector<bool*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				auto value{ ParseNumber<int>(input) };
				if (value.has_value()) {
					*e = static_cast<bool>(value.value());
				}
			}
		}
	};
	auto addSize_t = [](std::vector<size_t*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				auto value{ ParseNumber<std::size_t>(input) };
				if (value.has_value()) {
					*e = value.value();
				}
			}
		}
	};
	auto addInt = [](std::vector<int*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				auto value{ ParseNumber<int>(input) };
				if (value.has_value()) {
					*e = value.value();
				}
			}
		}
	};
	auto addFloat = [](std::vector<float*> entries, std::ifstream& file, std::string& input, auto nextEntry) {
		for (auto e : entries) {
			if (nextEntry(file, input)) {
				auto value{ ParseNumber<float>(input) };
				if (value.has_value()) {
					*e = value.value();
				}
			}
		}
	};
	std::string input;
	size_t temporary;
	std::vector<size_t*> size_tEntries = {
		// Global
		&constants.global.minRounds,
		&constants.global.currentTargetRound,
		&constants.global.maxRounds,
		&temporary,
	};
	addSize_t(size_tEntries, file, input, nextEntry);
	constants.window.current_resolution = static_cast<Resolution>(temporary);

	std::vector<bool*> boolEntries = {
		// Window
		&constants.window.startingModeFullScreen,
	};
	addBools(boolEntries, file, input, nextEntry);

	size_tEntries = {
		// Window
		&constants.window.FPS,
		// Player
		&constants.player.minPlayerCount,
		&constants.player.maxPlayerCount,
		// World
		&constants.world.minPlanetCount,
		&constants.world.maxPlanetCount,
		&constants.world.showPlanetCount,
	};
	addSize_t(size_tEntries, file, input, nextEntry);

	std::vector<int*> intEntries{
		// World
		&constants.world.minDimensionX,
		&constants.world.maxDimensionX,
		&constants.world.minDimensionY,
		&constants.world.maxDimensionY,

		&constants.world.showDimensionX,
		&constants.world.showDimensionY,

		&constants.world.discoverRange,
	};
	addInt(intEntries, file, input, nextEntry);

	boolEntries = {
		// Sound
		&constants.sound.muteVolume
	};
	addBools(boolEntries, file, input, nextEntry);

	std::vector<float*> floatEntries = {
		// Sound
		&constants.sound.masterVolume
	};
	addFloat(floatEntries, file, input, nextEntry);

	size_tEntries = {
		// Planet
		&constants.planet.maxShips,
		&constants.planet.startingHumanShipsMultiplicator,
		&constants.planet.startingGlobalShipsMultiplicator,
		&constants.planet.homeworldProduction,
		&constants.planet.minProduction,
		&constants.planet.maxProduction,
	};
	addSize_t(size_tEntries, file, input, nextEntry);

	floatEntries = {
		// Planet
		&constants.planet.homeworldSpacing,
		&constants.planet.globalSpacing,
	};
	addFloat(floatEntries, file, input, nextEntry);

	intEntries = {
		// Fleet
		&constants.fleet.minFleetSpeed,
		&constants.fleet.maxFleetSpeed,
	};
	addInt(intEntries, file, input, nextEntry);

	floatEntries = {
		// Fight
		&constants.fight.hitChance,
	};
	addFloat(floatEntries, file, input, nextEntry);
	file.close();

#ifdef _DEBUG
	constants.window.startingModeFullScreen = false;
#endif // _DEBUG

	Print("config loaded", PrintType::INFO);
}
void SaveConfig() {
	auto const& constants{ AppContext::GetInstance().constants };
	std::ofstream file{ };

	if (!std::filesystem::exists(constants.files.savesDir)) {
		Print("saves dir does not exists", PrintType::EXPECTED_ERROR);
		std::filesystem::create_directory(constants.files.savesDir);
		Print("saves dir generated", PrintType::INFO);
	}

	if (!std::filesystem::exists(constants.files.configFile())) {
		Print("config generated", PrintType::INFO);
	}

	file.open(constants.files.configFile());

	std::string toSave{ "//\n// Purpur Tentakel\n// Tentakels Attacking\n// Config\n//\n\n// Min Count >= 0\n" };


	auto headline = [](std::string const& headline, std::string& toSave) {
		toSave += "\n// " + headline + '\n';
	};
	auto entry = [](std::string const& entry, std::string const& message, std::string& toSave) {
		toSave += entry + ' ' + token + ' ' + message + "\n";
	};

	headline("Global", toSave);


	entry(std::to_string(constants.global.minRounds), "Min Game Rounds", toSave);
	entry(std::to_string(constants.global.currentTargetRound), "Current Target Game Round", toSave);
	entry(std::to_string(constants.global.maxRounds), "Max Game Rounds", toSave);



	headline("Window", toSave);
	entry(std::to_string(static_cast<int>(constants.window.current_resolution)), "contains the current solution as an enum", toSave);
	entry(std::to_string(constants.window.startingModeFullScreen), "Starting Full Screen (0 = window)", toSave);
	entry(std::to_string(constants.window.FPS), "Target FPS", toSave);

	headline("Player", toSave);
	entry(std::to_string(constants.player.minPlayerCount), "Min Player Count", toSave);
	entry(std::to_string(constants.player.maxPlayerCount), "Max Player Count", toSave);

	headline("World", toSave);
	entry(std::to_string(constants.world.minPlanetCount), "Min Planet Count", toSave);
	entry(std::to_string(constants.world.maxPlanetCount), "Max Planet Count", toSave);
	entry(std::to_string(constants.world.showPlanetCount), "Show Galaxy Planet Count", toSave);

	entry(std::to_string(constants.world.minDimensionX), "Min Dimension X", toSave);
	entry(std::to_string(constants.world.maxDimensionX), "Max Dimension X", toSave);
	entry(std::to_string(constants.world.minDimensionY), "Min Dimension Y", toSave);
	entry(std::to_string(constants.world.maxDimensionY), "Max Dimension Y", toSave);

	entry(std::to_string(constants.world.showDimensionX), "Show Galaxy Dimension X", toSave);
	entry(std::to_string(constants.world.showDimensionY), "Show Galaxy Dimension Y", toSave);

	entry(std::to_string(constants.world.discoverRange), "Discover Range of Space Objects", toSave);

	headline("Sound", toSave);
	entry(std::to_string(constants.sound.muteVolume), "Volume Mute (1 = mute)", toSave);
	entry(std::to_string(constants.sound.masterVolume), "Master Volume (0.0 - 100.0)", toSave);

	headline("Planet", toSave);
	entry(std::to_string(constants.planet.maxShips), "Max Ships", toSave);
	entry(std::to_string(constants.planet.startingHumanShipsMultiplicator), "Starting Ships Multiplicator for Humans", toSave);
	entry(std::to_string(constants.planet.startingGlobalShipsMultiplicator), "Starting Ships Multiplicator for Global", toSave);
	entry(std::to_string(constants.planet.homeworldProduction), "HomeWorld Production", toSave);
	entry(std::to_string(constants.planet.minProduction), "Min Production", toSave);
	entry(std::to_string(constants.planet.maxProduction), "Max Production", toSave);
	entry(std::to_string(constants.planet.homeworldSpacing), "Homeworld Spacing (0.0 - 1.0)", toSave);
	entry(std::to_string(constants.planet.globalSpacing), "Global Spacing (0.0 - 1.0)", toSave);

	headline("Fleet", toSave);
	entry(std::to_string(constants.fleet.minFleetSpeed), "Min Fleet Speed", toSave);
	entry(std::to_string(constants.fleet.maxFleetSpeed), "Max Fleet Speed", toSave);

	headline("Fight", toSave);
	entry(std::to_string(constants.fight.hitChance), "Hit Chance for a single ship", toSave);

	file << toSave;
	file.close();

	Print("config saved", PrintType::INFO);
}
