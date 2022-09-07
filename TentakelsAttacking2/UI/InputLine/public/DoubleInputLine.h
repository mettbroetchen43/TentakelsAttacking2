//
// Purpur Tentakel
// 07.09.2022
//

#pragma once
#include "InputLine.h"

class DoubleInputLine : public InputLine{
public:
	using InputLine::InputLine;
	[[nodiscard]] bool IsValidKey(int key) override;
};

