//
// Purpur Tentakel
// 28.10.2022
//

#include "HPrint.h"
#include <iostream>

void Print(std::string const& message, PrintType printType) {
	std::string toPrint = "[";
	switch (printType) {
		default:
		case PrintType::INFO:
			toPrint += "INFO";
			break;
		case PrintType::EXPECTED_ERROR:
			toPrint += "EXPECTED_ERROR";
			break;
		case PrintType::ERROR:
			toPrint += "ERROR";
			break;
		case PrintType::INITIALIZE:
			toPrint += "INITIALIZE";
			break;
		case PrintType::BUILD:
			toPrint += "BUILD";
			break;
	}

	toPrint += "] " + message + '\n';
	std::cout << toPrint;
}
