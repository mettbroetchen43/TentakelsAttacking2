//
// Purpur Tentakel
// 25.09.2022
//

#include "HTextProcessing.h"
#include "AppContext.h"
#include "HTextProcecingConstant.hpp"
#include "Allignment.h"
#include <raylib.h>
#include <string_view>

[[nodiscard]] std::vector<std::string> GetSerializedText(
	std::string const& text) {
	size_t lhs = 0;
	size_t rhs = 0;
	std::vector<std::string> toReturn;

	while (true) {
		rhs = text.find_first_of('\n', rhs + 1);
		if (rhs == std::string::npos) {
			toReturn.push_back(text.substr(lhs));
			break;
		}

		toReturn.push_back(text.substr(lhs, rhs - lhs));
		lhs = rhs + 1;
	}

	return toReturn;
}
[[nodiscard]] std::string GetStringFromVector(
	std::vector<std::string> const& slicedText) {

	std::string toReturn;

	for (auto const& s : slicedText) {
		toReturn += s;
	}

	return toReturn;
}


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

float GetElementTextHight(Vector2 const& size, float height) {
	return size.y * height;
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

void StripString(std::string& toStrip) {
	size_t pos1 = toStrip.find_first_not_of(' ');

	if (pos1 == std::string::npos) {
		toStrip = std::string();
		return;
	}

	size_t pos2 = toStrip.find_last_not_of(' ');
	toStrip = toStrip.substr(pos1, pos2 - pos1 + 1);
}

[[nodiscard]] std::vector<std::string> GetHorisontalAlignedText(
	std::vector<std::string> const& text, float fontSize,
	Rectangle colider, Vector2 spaceSize,
	Alignment alignment, AppContext const& appContext) {

	TextAlignment textAlignment =
		GetHorisontalTextAlignment(alignment);

	if (textAlignment == TextAlignment::LEFT) {
		return text;
	}

	std::vector<std::string> toReturn;
	for (auto const& t : text) {
		Vector2 textSize = MeasureTextEx(
			*(appContext.assetManager.GetFont()),
			t.c_str(),
			fontSize,
			0.0f
		);

		if (colider.width < textSize.x) {
			toReturn.push_back(t);
			continue;
		}

		float difference = colider.width - textSize.x;
		difference = textAlignment == TextAlignment::MID ?
			difference / 2 : difference;

		size_t spaceCount =
			static_cast<size_t>(difference / spaceSize.x);

		std::string entry(spaceCount, ' ');
		entry += t;
		toReturn.push_back(entry);
	}

	return toReturn;
}

[[nodiscard]] std::string GetVerticalAlignedText(
	std::string const& text, float fontSize,
	Rectangle colider, Vector2 spaceSize,
	Alignment alignment, AppContext const& appContext) {

	TextAlignment textAlignment =
		GetVerticalTextAlignment(alignment);

	if (textAlignment == TextAlignment::TOP) {
		return text;
	}

	Vector2 textSize = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		text.c_str(),
		fontSize,
		0.0f
	);

	if (colider.height < textSize.y) {
		return text;
	}

	float difference = colider.height - textSize.y;
	difference = textAlignment == TextAlignment::MID ?
		difference / 2 : difference;

	size_t newLineCount =
		static_cast<size_t>(difference / spaceSize.y);

	std::string toReturn(newLineCount, '\n');
	toReturn += text;

	return toReturn;
}

std::string GetAlignedText(std::string const& text,
	Rectangle colider, float fontSize,
	Alignment alignment) {

	AppContext& appContext = AppContext::GetInstance();

	Vector2 spaceSize = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		" ",
		fontSize,
		0.0f
	);
	std::vector<std::string> slicedText = GetSerializedText(text);

	slicedText = GetHorisontalAlignedText(
		slicedText,
		fontSize,
		colider,
		spaceSize,
		alignment,
		appContext
	);

	std::string toReturn = GetStringFromVector(slicedText);

	toReturn = GetVerticalAlignedText(
		toReturn,
		fontSize,
		colider,
		spaceSize,
		alignment,
		appContext
	);

	return toReturn;
}