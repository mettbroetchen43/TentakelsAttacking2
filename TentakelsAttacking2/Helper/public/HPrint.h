//
// Purpur Tentakel
// 28.10.2022
//

#pragma once
#include <string>

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

/**
 * print to the console with a print type tag.
 */
void Print(std::string const& message, PrintType printType);