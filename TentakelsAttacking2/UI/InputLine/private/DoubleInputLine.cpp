#include "DoubleInputLine.h"

bool DoubleInputLine::IsValidKey(int key) {
	bool valid = (key >= 48 and key <= 57) // numbers
		or key == 44 // comma
		or key == 46; // dot

	//check for multiple commas/dots
	if ('.' == key or ',' == key) {
		if (m_input.size() == 0) {
			valid = false;
		}

		for (char c : m_input) {
			if ('.' == c or ',' == c) {
				valid = false;
				break;
			}
		}
	}

	return valid;
}
