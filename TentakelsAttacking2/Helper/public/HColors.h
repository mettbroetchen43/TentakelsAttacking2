//
// Purpur Tentakel
// 20.10.2022
//

#pragma once
#include <array>
#include <raylib.h>

struct Colors {
private:
	using ColorArray = std::array<Color, 16>;
	ColorArray m_colors = {
	YELLOW,
	GOLD,
	PINK,
	MAGENTA,
	ORANGE,
	RED,
	MAROON,
	GREEN,
	LIME,
	DARKGREEN,
	SKYBLUE,
	BLUE,
	DARKBLUE,
	PURPLE,
	VIOLET,
	DARKPURPLE,
	};

public:
	bool CheckValidColor(Color& color);

	[[nodiscard]] ColorArray GetColors() const;
};
