//
// Purpur Tentakel
// 10.12.2022
//

#include "CWindow.h"
#include "HPrint.h"
#include <raylib.h>

bool CWindow::IsPossibleResolution(Resolution toProove) {
	int screen = GetCurrentMonitor();
	int height = GetMonitorHeight(screen);
	int width = GetMonitorWidth(screen);

	auto value = GetIntFromResolution(toProove);

	if (width < value[0]) { return false; }
	if (height < value[1]) { return false; }
	return true;
}

std::vector<std::pair<Resolution,std::string>> CWindow::GetAllResolutionsAsString() {
	std::vector<std::pair<Resolution,std::string>> toReturn;

	for (int i = 0; i != static_cast<int>(Resolution::LAST); ++i) {

		Resolution entry = static_cast<Resolution>(i);

		if (!IsPossibleResolution(entry)) { continue; }

		toReturn.emplace_back(entry, GetStringFromResolution(entry));
	}

	return toReturn;
}

std::string CWindow::GetStringFromResolution(Resolution resolution) {
	switch (resolution) {
	case Resolution::UHD:
		return "UHD 16:9 (3840 x 2162)";
	case Resolution::WQHD:
		return "WQHD 16:9 (2560 x 1440)";
	case Resolution::FULL_HD:
		return "Full HD 16:9 (1920 x 1080)";
	case Resolution::HD:
		return "HD 16:9 (1280 x 720)";
	case Resolution::SCREEN: {
		auto value = GetIntFromResolution(resolution);
		return "Screen (" + std::to_string(value[0]) + " x " + std::to_string(value[1]) + ")";
	}
	case Resolution::LAST:
	default:
		Print("invalud resoltion selected: " + static_cast<int>(resolution), PrintType::ERROR);
		return "invalid Resoluion";
	}
}

std::array<int, 2> CWindow::GetIntFromResolution(Resolution resolution) {
	switch (resolution) {
	case Resolution::UHD:
		return  { 3840,2162 };
	case Resolution::WQHD:
		return { 2560,1440 };
	case Resolution::FULL_HD:
		return { 1920, 1080 };
	case Resolution::HD:
		return { 1280,720 };
	case Resolution::SCREEN: {
		int screen = GetCurrentMonitor();
		int height = GetMonitorHeight(screen);
		int width = GetMonitorWidth(screen);

		return { width,height };
	}
	case Resolution::LAST:
	default:
		Print("invalud resoltion selected: " + static_cast<int>(resolution), PrintType::ERROR);
		return { 100,100 };
	}
}
