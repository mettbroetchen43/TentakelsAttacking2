//
// Purpur Tentakel
// 28.10.2022
//

#include "HPrint.h"
#include "HErrorLog.h"

[[nodiscard]] static std::string GetPrintTypeString(PrintType printType) {
	switch (printType) {
		default:
		case PrintType::INFO:
			return "[INFO]";
		case PrintType::EXPECTED_ERROR:
			return "[EXPECTED_ERROR]";
		case PrintType::ERROR:
			return "[ERROR]";
		case PrintType::INITIALIZE:
			return "[INITIALIZE]";
		case PrintType::BUILD:
			return "[BUILD]";
		case PrintType::DEBUG:
			return "[DEBUG]";
	}
}

static void TryExport(std::string const& message, PrintType printType) {
	switch (printType) {
		case PrintType::EXPECTED_ERROR:
		case PrintType::ERROR:
			LogError(message);
			break;
		default:
			break;
	}
}

void Print(std::string const& message, PrintType printType) {

	std::string const typeS   { GetPrintTypeString(printType) };
	std::string const toExport{ typeS + " " + message + '\n'  };

	TryExport(toExport, printType);
	std::cout << std::setw(GetPrintTypeString(longestType).size()) << typeS << ' ' << message << '\n';
}
