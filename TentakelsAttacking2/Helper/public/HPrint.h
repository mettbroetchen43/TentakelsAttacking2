//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>
#include <iostream>
#include <iomanip>

#ifdef USE_FMT_FORMAT
#include <fmt/format.h> // for ubuntu CI -> gcc 12
#else
#include <format>
#endif

/**
 * provides all kinds of print types.
 */
enum class PrintType {
	INFO,
	EXPECTED_ERROR,
	ERROR,
	INITIALIZE,
	BUILD,
	DEBUG,
};
static PrintType longestType{PrintType::EXPECTED_ERROR};

/**
 * returns the provided print type as string.
 */
[[nodiscard]] static std::string GetPrintTypeString(PrintType printType);
/**
 * exports the message when according to the print type.
 */
static void TryExport(std::string const& message, PrintType printType);

/**
 * print to the console with a print type tag and additional values.
 * values must match with the provided `{}` inside the string.
 */
template<typename... Args>
void Print(std::string const& message, PrintType printType, Args const&... args);
/**
 * print to the console with a print type tag.
 */
void Print(std::string const& message, PrintType printType);

template<typename ...Args>
inline void Print(std::string const& message, PrintType printType, Args const & ...args) {
#ifdef USE_FMT_FORMAT
	using namespace fmt;
#else
	using namespace std;
#endif // USE_FMT_FORMAT
	std::string const typeS   { GetPrintTypeString(printType) };
	std::string const toExport{ typeS + ' ' + message + '\n'  };
	try {
		std::string out{vformat(message, make_format_args(args...))};
		std::cout << std::setw(GetPrintTypeString(longestType).size()) << typeS << ' ' << out << '\n';
		TryExport(toExport, printType);

	}
	catch (format_error const&) {
		Print("format while printing", PrintType::ERROR);
		std::cout << std::setw(GetPrintTypeString(longestType).size()) << typeS << ' ' << message << '\n';
		TryExport(toExport, printType);
	}
	catch (std::bad_alloc const&) {
		Print("bad alloc while printing with arguments", PrintType::ERROR);
		std::cout << std::setw(GetPrintTypeString(longestType).size()) << typeS << ' ' << message << '\n';
		TryExport(toExport, printType);
	}
}
