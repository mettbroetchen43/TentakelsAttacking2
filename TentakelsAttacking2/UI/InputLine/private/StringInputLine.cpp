//
// Purpur Tentakel
// 06.09.2022
//

#include "StringInputLine.h"

bool StringInputLine::IsValidKey(int key) {
	bool valid = key >= 32 and
		key <= 126;

	return valid;
}
