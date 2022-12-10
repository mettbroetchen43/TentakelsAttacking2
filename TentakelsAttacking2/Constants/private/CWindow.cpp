//
// Purpur Tentakel
// 10.12.2022
//

#include "CWindow.h"
#include "HPrint.h"

std::vector<std::string> CWindow::GetAllResolutionsAsString() {
	std::vector<std::string> toReturn;

	for ( Resolution entry = Resolution::UHD; entry != Resolution::LAST;) {
		toReturn.push_back ( GetStringFromResolution ( entry ) );

		auto temporary = static_cast<int>(entry);
		++temporary;
		entry = static_cast<Resolution>(temporary);
	}

	return toReturn;
}

std::string CWindow::GetStringFromResolution ( Resolution resolution ) {
	switch ( resolution ) {
		case Resolution::UHD:
			return "UHD (3840 x 2162)";
		case Resolution::FULL_HD:
			return "Full HD (1920 x 1080)";
		case Resolution::HD:
			return "HD (1280 x 720)";
		case Resolution::LAST:
		default:
			Print ( "invalud resoltion selected: " + static_cast<int>(resolution), PrintType::ERROR );
			return "invalid Resoluion";
	}
}

std::array<int, 2> CWindow::GetIntFromResolution ( Resolution resolution ) {
	switch ( resolution ) {
		case Resolution::UHD:
			return  { 3840,2162 };
		case Resolution::FULL_HD:
			return { 1920, 1080 };
		case Resolution::HD:
			return { 1280,720 };
		case Resolution::LAST:
		default:
			Print ( "invalud resoltion selected: " + static_cast<int>(resolution), PrintType::ERROR );
			return { 100,100 };
	}
}
