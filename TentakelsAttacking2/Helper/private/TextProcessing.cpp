//
// Purpur Tentakel
// 25.09.2022
//

#include "TextProcessing.h"
#include "AppContext.h"
#include "TextProcecingConstant.hpp"
#include <raylib.h>
#include <string_view>


void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext const& appContext) {
	size_t lhs = 0;
	size_t rhs = 0;

	while (true) {
		rhs = toBreak.find_first_of(' ', rhs + 1);
		if (rhs == std::string::npos) {
			break;
		}

		std::string line(toBreak.c_str() + lhs, rhs - lhs);
		Vector2 textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			line.data(),
			fontSize,
			0.0f
		);

		if (textSize.x > length) {
			rhs = toBreak.find_last_of(' ', rhs - 1);
			if (rhs == std::string::npos) {
				rhs = toBreak.find_first_of(' ');
				if (rhs == std::string::npos) {
					break;
				}
			}
			toBreak.at(rhs) = '\n';
			lhs = rhs + 1;
		}
	}
}

std::string GetPritableTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext) {
	Vector2 textSize = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		(text + Constants::c_enter).c_str(),
		fontSize,
		0.0f);
	if ((textSize.x + Constants::c_cursorOffset) < colider.width) {
		return text;
	}

	std::string toReturn = text;
	std::string toCheck = Constants::c_prefix + text + Constants::c_enter;

	do {
		toReturn = toReturn.substr(1, toReturn.size());
		toCheck = Constants::c_prefix + toReturn + Constants::c_enter;
		textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			toCheck.c_str(),
			fontSize,
			0.0f);
	} while (textSize.x + Constants::c_cursorOffset >= colider.width);

	return Constants::c_prefix + toReturn;
}
std::string GetPritablePlaceholderTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext) {
	Vector2 textSize = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		text.c_str(),
		fontSize,
		0.0f);
	if ((textSize.x + Constants::c_cursorOffset) < colider.width) {
		return text;
	}

	std::string toReturn = text;
	std::string toCheck = Constants::c_prefix + text;

	do {
		toReturn = toReturn.substr(0, toReturn.size() - 1);
		toCheck = Constants::c_prefix + toReturn;
		textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			toCheck.c_str(),
			fontSize,
			0.0f);
	} while (textSize.x + Constants::c_cursorOffset >= colider.width);

	return  toReturn + Constants::c_prefix;
}
