//
// Purpur Tentakel
// 06.09.2022
//

#include "IntInputLine.h"

bool IntInputLine::IsValidKey(int key) {
	bool valid = key >= 48 and
		key <= 57;

	return valid;
}
