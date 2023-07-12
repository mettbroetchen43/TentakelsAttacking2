//
// Purpur Tentakel
// 27.10.2022
//

#include "ConfigIO.h"
#include "AppContext.h"
#include "HPrint.h"
#include "HConfigEnum.h"
#include <filesystem>
#include <nlohmann/json.hpp>
#include <cassert>

// string defaults
static std::string const defaultValuePrefix{ "-> using default value -> overwrite config by save" };
static int loadEntryCount{ 0 }; 
// print
auto const printMissingSection{ [](ConfigTypes section) {
	Print(
		PrintType::ERROR,
		"section \"{}\" in config missing {}",
		CToS(section),
		defaultValuePrefix
	);
} };
auto const printMissingEntry{ [](ConfigTypes entry) {
	Print(
		PrintType::ERROR,
		"entry \"{}\" in config missing {}",
		CToS(entry),
		defaultValuePrefix
	);
} };
auto const printNotMatchingCount{ [](ConfigTypes section, int expected, size_t provided) {
	Print(
		PrintType::ERROR,
		"section \"{}\" entry count in config is not matching -> expected: \"{}\" -> provided: \"{}\"",
		CToS(section),
		expected,
		provided
		);
} };
auto const printWrongDatatype{ [](ConfigTypes entry) {
	Print(
		PrintType::ERROR,
		"entry \"{}\" in config has wrong datatype {}",
		CToS(entry),
		defaultValuePrefix
		);
} };

// check
auto const isNull{ [](nlohmann::json const& son, ConfigTypes type) ->bool {
	assert(not son.is_null());
	if (son.is_array()) {
		printMissingSection(type);
		return true;
	}
	return false;
} };
auto const isExistingSection{ [](nlohmann::json const& son, ConfigTypes type) ->bool {
	assert(son.contains(CToS(type)));
	if (not son.contains(CToS(type))) {
		printMissingSection(type);
		return false;
	}
	return true;
} };
auto const isExistingEntry{ [](nlohmann::json const& son, ConfigTypes type) ->bool {
	assert(son.contains(CToS(type)));
	if (not son.contains(CToS(type))) {
		printMissingEntry(type);
		return false;
	}
	return true;
} };
auto const isMatchingSize{ [](nlohmann::json const& son, ConfigTypes section, int count) ->bool {
	assert(son.size() == count);
	if (son.size() != count) {
		printNotMatchingCount(section, count, son.size());
		return false;
	}
	return true;
} };

// load
auto const loadSection{ [](nlohmann::json const& son, nlohmann::json& out, ConfigTypes section, int count)->bool {
	if (not isExistingSection(son, section)) {
		return false;
	}
	son.at(CToS(section)).get_to(out);

	if (isNull(out, section)) { return false; }
	isMatchingSize(out, section, count);

	return true;
} };
auto const loadString{ [](nlohmann::json const& son, std::string& out, ConfigTypes entry) -> bool  {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;
	
	}
	assert(son.at(CToS(entry)).is_string());
	if (not son.at(CToS(entry)).is_string()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };
auto const loadInt{ [](nlohmann::json const& son, int& out, ConfigTypes entry) -> bool {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;

	}
	assert(son.at(CToS(entry)).is_number_integer());
	if (not son.at(CToS(entry)).is_number_integer()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };
auto const loadFloat{ [](nlohmann::json const& son, float& out, ConfigTypes entry) -> bool {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;

	}
	assert(son.at(CToS(entry)).is_number_float());
	if (not son.at(CToS(entry)).is_number_float()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };
auto const loadBool{ [](nlohmann::json const& son, bool& out, ConfigTypes entry) -> bool {
	++loadEntryCount;
	if (not isExistingEntry(son, entry)) {
		return false;

	}
	assert(son.at(CToS(entry)).is_boolean());
	if (not son.at(CToS(entry)).is_boolean()) {
		printWrongDatatype(entry);
		return false;
	}

	son.at(CToS(entry)).get_to(out);
	return true;
} };

void LoadConfig() {
	// load file
	loadEntryCount = { 0 };
	auto& constants = AppContext::GetInstance().constants;
	std::ifstream file;

	if (!std::filesystem::exists(constants.files.configFile())) {
		Print(PrintType::EXPECTED_ERROR, "no config existing");
		SaveConfig();
		return;
	}

	file.open(constants.files.configFile());
	if (!file.is_open()) {
		Print(PrintType::INFO, "cant open config");
		return;
	}

	nlohmann::json load;
	file >> load;
	file.close();

	// from json
	// config
	if (isNull(load, ConfigTypes::CONFIFG)) { 
		Print(
			PrintType::ERROR,
			"provided config is null {}",
			defaultValuePrefix
		);
		return;
	}
	if (not isMatchingSize(load, ConfigTypes::CONFIFG, constants.global.configSectionCount)) {
		Print(
			PrintType::ERROR,
			"config section count is not matching {} -> expected: {} -> provided: {}",
			defaultValuePrefix,
			constants.global.configSectionCount,
			load.size()
		);
	};
	// version
	if (nlohmann::json version; loadSection(load, version, ConfigTypes::VERSION, constants.global.configVersionCount)) {
		if (std::string versionConfig; loadString(version, versionConfig, ConfigTypes::VERSION_CONFIG)) {
			if (versionConfig != constants.global.configVersion) {
				Print(
					PrintType::ERROR,
					"config version in config is not matching -> expected: {} -> provided: {} -> overwrite config by save",
					constants.global.configVersion,
					versionConfig
				);
			}
		}
		else {
			Print(PrintType::ERROR, "unable to check if config version is matching");
		}
		if (std::string versionGame; loadString(version, versionGame, ConfigTypes::VERSION_GAME)) {
			if (versionGame != constants.global.gameVersion) {
				Print(
					PrintType::ERROR,
					"game version in config is not matching -> expected: {} -> provided: {} -> overwrite by save",
					constants.global.gameVersion,
					versionGame
				);
			}
		}
		else {
			Print(PrintType::ERROR, "unable to check if config version is matching");
		}
	}
	else {
		Print(PrintType::ERROR, "not able to check if config and game versions match");
	}
	// fight
	if (nlohmann::json fight; loadSection(load, fight, ConfigTypes::FIGHT, constants.fight.configEntryCount)) {
		if (float out; loadFloat(fight, out, ConfigTypes::HIT_CHANCE))        { constants.fight.hitChance =       out; }
		if (int out;     loadInt(fight, out, ConfigTypes::FLEET_FIGHT_RANGE)) { constants.fight.fleetFightRange = out; }
	}
	// fleet
	if (nlohmann::json fleet; loadSection(load, fleet, ConfigTypes::FLEET, constants.fleet.configEntryCount)) {
		if (int out; loadInt(fleet, out, ConfigTypes::FLEET_SPEED_CURRENT)) { constants.fleet.currentFleetSpeed = out; }
		if (int out; loadInt(fleet, out, ConfigTypes::FLEET_SPEED_MAX))     { constants.fleet.maxFleetSpeed     = out; }
		if (int out; loadInt(fleet, out, ConfigTypes::FLEET_SPEED_MIN))     { constants.fleet.minFleetSpeed     = out; }
	}
	// global
	if (nlohmann::json global; loadSection(load, global, ConfigTypes::GLOBAL, constants.global.configEntryCount)) {
		if (std::string out; loadString(global, out, ConfigTypes::CURRENT_LANGUAGE_NAME)) { constants.global.currentLanguageName = out; }
		if (int         out;    loadInt(global, out, ConfigTypes::GAME_ROUNDS_CURRENT))   { constants.global.currentTargetRound  = out; }
		if (int         out;    loadInt(global, out, ConfigTypes::GAME_ROUNDS_MAX))       { constants.global.maxRounds           = out; }
		if (int         out;    loadInt(global, out, ConfigTypes::GAME_ROUNDS_MIN))       { constants.global.minRounds           = out; }
	}
	// planet
	if (nlohmann::json planet; loadSection(load, planet, ConfigTypes::PLANET, constants.planet.configEntryCount)) {
		if (int   out;   loadInt(planet, out, ConfigTypes::PRODUCTION_HOMEWORLD))                { constants.planet.homeworldProduction              = out; }
		if (int   out;   loadInt(planet, out, ConfigTypes::PRODUCTION_MAX))                      { constants.planet.maxProduction                    = out; }
		if (int   out;   loadInt(planet, out, ConfigTypes::PRODUCTION_MIN))                      { constants.planet.minProduction                    = out; }
		if (int   out;   loadInt(planet, out, ConfigTypes::SHIPS_MAX_FACTOR))                    { constants.planet.maxShipsFactor                   = out; }
		if (float out; loadFloat(planet, out, ConfigTypes::SPACEING_GLOBAL))                     { constants.planet.globalSpacing                    = out; }
		if (float out; loadFloat(planet, out, ConfigTypes::SPACEING_HOMEWORLD))                  { constants.planet.homeworldSpacing                 = out; }
		if (int   out;   loadInt(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_GLOBAL)) { constants.planet.startingGlobalShipsMultiplicator = out; }
		if (int   out;   loadInt(planet, out, ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_HUMAN))  { constants.planet.startingHumanShipsMultiplicator  = out; }
	}
	// player
	if (nlohmann::json player; loadSection(load, player, ConfigTypes::PLAYER, constants.player.configEntryCount)) {
		if (int out; loadInt(player, out, ConfigTypes::PLAYER_COUNT_MAX)) { constants.player.maxPlayerCount = out; }
		if (int out; loadInt(player, out, ConfigTypes::PLAYER_COUNT_MIN)) { constants.player.minPlayerCount = out; }
	}
	// sound
	if (nlohmann::json sound; loadSection(load, sound, ConfigTypes::SOUND, constants.sound.configEntryCount)) {
		if (float out; loadFloat(sound, out, ConfigTypes::VOLUME_MASTER))    { constants.sound.masterVolume = out; }
		if (bool  out;  loadBool(sound, out, ConfigTypes::VOLUME_MUTE_BOOL)) { constants.sound.muteVolume   = out; }
	}
	// window
	if (nlohmann::json window; loadSection(load, window, ConfigTypes::WINDOW, constants.window.configEntryCount)) {
		if (int  out;  loadInt(window, out, ConfigTypes::RESOLUTION_AS_ENUM))     { constants.window.current_resolution = static_cast<Resolution>(out); }
		if (bool out; loadBool(window, out, ConfigTypes::FULL_SCREEN_START_BOOL)) { constants.window.startingModeFullScreen                     = out ; }
		if (int  out;  loadInt(window, out, ConfigTypes::TARGET_FPS))             { constants.window.FPS                                        = out ; }
	}
	// world
	if (nlohmann::json world; loadSection(load, world, ConfigTypes::WORLD, constants.world.configEntryCount)) {
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_CURRENT))      { constants.world.currentDimensionX   = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_MAX))          { constants.world.maxDimensionX       = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_MIN))          { constants.world.minDimensionX       = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_X_SHOW_GALAXY))  { constants.world.showDimensionX      = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_CURRENT))      { constants.world.currentDimensionY   = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_MAX))          { constants.world.maxDimensionY       = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_MIN))          { constants.world.minDimensionY       = out; }
		if (int out; loadInt(world, out, ConfigTypes::DIMENSION_Y_SHOW_GALAXY))  { constants.world.showDimensionY      = out; }
		if (int out; loadInt(world, out, ConfigTypes::DISCOVER_RANGE_FACTOR))    { constants.world.discoverRangeFactor = out; }
		if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_CURRENT))     { constants.world.currentPlanetCount  = out; }
		if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_MAX))         { constants.world.maxPlanetCount      = out; }
		if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_MIN))         { constants.world.minPlanetCount      = out; }
		if (int out; loadInt(world, out, ConfigTypes::PLANET_COUNT_SHOW_GALAXY)) { constants.world.showPlanetCount     = out; }
	}

	// check if all values are loaded
	AppContext_ty_c appContext = AppContext::GetInstance();
	assert(loadEntryCount == appContext.constants.GetConfigValueCount());
	if (int count = appContext.constants.GetConfigValueCount();  loadEntryCount != count) {
		Print(
			PrintType::ERROR,
			"Entry count in config is not matching -> expected: {} -> provided: {}",
			count,
			loadEntryCount
		);
	} else {
		Print(PrintType::INFO, "Entry count in config is matching");
	}

#ifdef _DEBUG
	constants.window.startingModeFullScreen = false;
	Print(PrintType::DEBUG, "set full screen to false");
	constants.window.current_resolution = Resolution::HD;
	Print(PrintType::DEBUG, "set resolution ro HD");
#endif // _DEBUG

	Print(PrintType::INFO, "config loaded");
}
void SaveConfig() {
	
	// to json
	auto const& constants{ AppContext::GetInstance().constants };
	nlohmann::json save;
	
	save[CToS(ConfigTypes::GAME_EVENTS)] = {
		{ CToS(ConfigTypes::PIRATES),             constants.gameEvents.IsFlag(HGameEventType::PIRATES)        },
		{ CToS(ConfigTypes::REVOLTS),             constants.gameEvents.IsFlag(HGameEventType::REVOLTS)        },
		{ CToS(ConfigTypes::RENEGADE_SHIPS),      constants.gameEvents.IsFlag(HGameEventType::RENEGADE_SHIPS) },
		{ CToS(ConfigTypes::BLACK_HOLE),          constants.gameEvents.IsFlag(HGameEventType::BLACK_HOLE)     },
		{ CToS(ConfigTypes::SUPERNOVA),           constants.gameEvents.IsFlag(HGameEventType::SUPERNOVA)      },
		{ CToS(ConfigTypes::ENGINE_PROBLEM),      constants.gameEvents.IsFlag(HGameEventType::ENGINE_PROBLEM) },
		{ CToS(ConfigTypes::GLOBAL_EVENT_CHANCE), constants.gameEvents.globalEventChance                      },
	};
	save[CToS(ConfigTypes::FIGHT)] = {
		{ CToS(ConfigTypes::HIT_CHANCE),        constants.fight.hitChance       },
		{ CToS(ConfigTypes::FLEET_FIGHT_RANGE), constants.fight.fleetFightRange },
	};
	save[CToS(ConfigTypes::FLEET)] = {
		{ CToS(ConfigTypes::FLEET_SPEED_CURRENT), constants.fleet.currentFleetSpeed },
		{ CToS(ConfigTypes::FLEET_SPEED_MAX),     constants.fleet.maxFleetSpeed     },
		{ CToS(ConfigTypes::FLEET_SPEED_MIN),     constants.fleet.minFleetSpeed     },
	};
	save[CToS(ConfigTypes::GLOBAL)] = {
		{ CToS(ConfigTypes::CURRENT_LANGUAGE_NAME), constants.global.currentLanguageName },
		{ CToS(ConfigTypes::GAME_ROUNDS_CURRENT),   constants.global.currentTargetRound    },
		{ CToS(ConfigTypes::GAME_ROUNDS_MAX),       constants.global.maxRounds             },
		{ CToS(ConfigTypes::GAME_ROUNDS_MIN),       constants.global.minRounds             },
	};
	save[CToS(ConfigTypes::PLANET)] = {
		{ CToS(ConfigTypes::PRODUCTION_HOMEWORLD),                constants.planet.homeworldProduction              },
		{ CToS(ConfigTypes::PRODUCTION_MAX),                      constants.planet.maxProduction                    },
		{ CToS(ConfigTypes::PRODUCTION_MIN),                      constants.planet.minProduction                    },
		{ CToS(ConfigTypes::SHIPS_MAX_FACTOR),                    constants.planet.maxShipsFactor                   },
		{ CToS(ConfigTypes::SPACEING_GLOBAL),                     constants.planet.globalSpacing                    },
		{ CToS(ConfigTypes::SPACEING_HOMEWORLD),                  constants.planet.homeworldSpacing                 },
		{ CToS(ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_GLOBAL), constants.planet.startingGlobalShipsMultiplicator },
		{ CToS(ConfigTypes::STARTING_SHIPS_MULTIPLICATOR_HUMAN),  constants.planet.startingHumanShipsMultiplicator  },
	};
	save[CToS(ConfigTypes::PLAYER)] = {
		{ CToS(ConfigTypes::PLAYER_COUNT_MAX), constants.player.maxPlayerCount },
		{ CToS(ConfigTypes::PLAYER_COUNT_MIN), constants.player.minPlayerCount },
	};
	save[CToS(ConfigTypes::SOUND)] = {
		{ CToS(ConfigTypes::VOLUME_MASTER),    constants.sound.masterVolume },
		{ CToS(ConfigTypes::VOLUME_MUTE_BOOL), constants.sound.muteVolume   },
	};
	save[CToS(ConfigTypes::VERSION)] = {
		{ CToS(ConfigTypes::VERSION_CONFIG),      constants.global.configVersion },
		{ CToS(ConfigTypes::VERSION_GAME),        constants.global.gameVersion   },
	};
	save[CToS(ConfigTypes::WINDOW)] = {
		{ CToS(ConfigTypes::RESOLUTION_AS_ENUM),       static_cast<size_t>(constants.window.current_resolution)     },
		{ CToS(ConfigTypes::FULL_SCREEN_START_BOOL),                       constants.window.startingModeFullScreen  },
		{ CToS(ConfigTypes::TARGET_FPS),                                   constants.window.FPS                     },
	};
	save[CToS(ConfigTypes::WORLD)] = {
		{ CToS(ConfigTypes::DIMENSION_X_CURRENT),      constants.world.currentDimensionX  },
		{ CToS(ConfigTypes::DIMENSION_X_MAX),          constants.world.maxDimensionX      },
		{ CToS(ConfigTypes::DIMENSION_X_MIN),          constants.world.minDimensionX      },
		{ CToS(ConfigTypes::DIMENSION_X_SHOW_GALAXY),  constants.world.showDimensionX     },
		{ CToS(ConfigTypes::DIMENSION_Y_CURRENT),      constants.world.currentDimensionY  },
		{ CToS(ConfigTypes::DIMENSION_Y_MAX),          constants.world.maxDimensionY      },
		{ CToS(ConfigTypes::DIMENSION_Y_MIN),          constants.world.minDimensionY      },
		{ CToS(ConfigTypes::DIMENSION_Y_SHOW_GALAXY),  constants.world.showDimensionY     },
		{ CToS(ConfigTypes::DISCOVER_RANGE_FACTOR),           constants.world.discoverRangeFactor      },
		{ CToS(ConfigTypes::PLANET_COUNT_CURRENT),     constants.world.currentPlanetCount },
		{ CToS(ConfigTypes::PLANET_COUNT_MAX),         constants.world.maxPlanetCount     },
		{ CToS(ConfigTypes::PLANET_COUNT_MIN),         constants.world.minPlanetCount     },
		{ CToS(ConfigTypes::PLANET_COUNT_SHOW_GALAXY), constants.world.showPlanetCount    },
	};

	// saving
	std::ofstream file{ };

	if (!std::filesystem::exists(constants.files.savesDir)) {
		Print(PrintType::EXPECTED_ERROR, "saves dir does not exists");
		std::filesystem::create_directory(constants.files.savesDir);
		Print(PrintType::INFO, "saves dir generated");
	}

	if (!std::filesystem::exists(constants.files.configFile())) {
		Print(PrintType::INFO, "config generated");
	}

	file.open(constants.files.configFile());

	file << save.dump(4);
	file.close();

	Print(PrintType::INFO, "config saved");
}
