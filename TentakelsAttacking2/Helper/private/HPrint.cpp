//
// Purpur Tentakel
// 28.10.2022
//

#include "HPrint.h"
#include "HErrorLog.h"
#include <iostream>

void Print(std::string const& message, PrintType printType) {
	std::string toPrint = "[";
	bool logError = false;
	switch (printType) {
		default:
		case PrintType::INFO:
			toPrint += "INFO";
			break;
		case PrintType::EXPECTED_ERROR:
			toPrint += "EXPECTED_ERROR";
			logError = true;
			break;
		case PrintType::ERROR:
			toPrint += "ERROR";
			logError = true;
			break;
		case PrintType::INITIALIZE:
			toPrint += "INITIALIZE";
			break;
		case PrintType::BUILD:
			toPrint += "BUILD";
			break;
		case PrintType::DEBUG:
			toPrint += "DEBUG";
			break;
	}

	toPrint += "] " + message + '\n';
	if (logError) {
		LogError(toPrint);
	}
	std::cout << toPrint;
}
