//
// Purpur Tentakel
// 20.10.2022
//

#include "HColors.h"
#include "UIEvents.hpp"
#include "HGeneral.h"

bool Colors::CheckValidColor(Color& color) {
	return std::find(m_colors.begin(), m_colors.end(), color)
		== m_colors.end();
}
Colors::ColorArray Colors::GetColors() const {
    return m_colors;
}
std::string Colors::AsString(Color color) {
	     if (AreSame(color, YELLOW))     { return "Yellow"; }
	else if (AreSame(color, GOLD))       { return "Gold"; }
	else if (AreSame(color, PINK))       { return "Pink"; }
	else if (AreSame(color, MAGENTA))    { return "Magenta"; }
	else if (AreSame(color, ORANGE))     { return "Orange"; }
	else if (AreSame(color, RED))        { return "Red"; }
	else if (AreSame(color, MAROON))     { return "Maroon"; }
	else if (AreSame(color, NECRO))      { return "Necro"; }
	else if (AreSame(color, LIME))       { return "Lime"; }
	else if (AreSame(color, DARKGREEN))  { return "Dark Green"; }
	else if (AreSame(color, SKYBLUE))    { return "Sky Blue"; }
	else if (AreSame(color, BLUE))       { return "Blue"; }
	else if (AreSame(color, DARKBLUE))   { return "Dark Blue"; }
	else if (AreSame(color, PURPLE))     { return "Purple"; }
	else if (AreSame(color, VIOLET))     { return "Violet"; }
	else if (AreSame(color, DARKPURPLE)) { return "Dark Purple"; }
	else                                 { return "Invalid Color"; }
}
bool Colors::AreSame(Color lhs, Color rhs) {
	return  lhs.r == rhs.r
		and lhs.g == rhs.g
		and lhs.b == rhs.b
		and lhs.a == rhs.a;
}
