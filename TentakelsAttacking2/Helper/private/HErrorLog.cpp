//
// Purpur Tentakel
// 01.01.2023
//

#include "HErrorLog.h"
#include "AppContext.h"
#include "HPrint.h"
#include <filesystem>
#include <chrono>

/**
 * sets the name if the current error log file based on the chrono timestamp.
 */
void SetErrorLogFileName() {
	auto& files{ AppContext::GetInstance().constants.files };

	auto const now{ std::chrono::system_clock::now() };
	std::stringstream filename{ };
	filename << "tentakels_attacking_debug_" << now.time_since_epoch().count() << ".txt";

	files.SetDebugLogFile(filename.str());
	Print("debug file name set", PrintType::INFO);
}

/**
 * opens the error log file.
 * creates the dirs and file if needed.
 */
void GenerateFileStream() {
	auto& files{ AppContext::GetInstance().constants.files };

	SetErrorLogFileName();

	if (!std::filesystem::exists(files.debugLogDir())) {
		std::filesystem::create_directories(files.debugLogDir());
		Print("created debug directory", PrintType::INFO);
	}
	else if (!std::filesystem::is_directory(files.debugLogDir())) {
		std::filesystem::remove(files.debugLogDir());
		std::filesystem::create_directories(files.debugLogDir());
		Print("removed debug file and added debug directory", PrintType::INFO);
	}

	files.debugLogStream.open(files.debugLogFile());
	Print("opened debug log", PrintType::INFO);
}

void LogError(std::string const& error) {
	auto& files{ AppContext::GetInstance().constants.files };

	if (!files.debugLogStream.is_open()) {
		GenerateFileStream();
	}

	files.debugLogStream << error;
	Print("logged error", PrintType::INFO);
}

void CloseErrorStream() {
	auto& files{ AppContext::GetInstance().constants.files };

	if (!files.debugLogStream.is_open()) {
		return;
	}

	files.debugLogStream.close();
	Print("closed debug log", PrintType::INFO);
}
