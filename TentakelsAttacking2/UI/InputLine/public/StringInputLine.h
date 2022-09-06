//
// Purpur Tentakel
// 06.09.2022
//

#pragma once
#include "InputLine.h"

class StringInputLine : public InputLine {
private:
	[[nodiscard]] bool IsValidKey(int key) override;
public:
	using InputLine::InputLine;
};

