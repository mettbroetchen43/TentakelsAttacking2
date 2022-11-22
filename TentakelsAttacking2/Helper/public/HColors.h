//
// Purpur Tentakel
// 20.10.2022
//

#pragma once
#include <array>
#include <raylib.h>

/**
 * contains all available colors of the game and validates it.
 */
struct Colors final {
private:
	using ColorArray = std::array<Color, 16>; ///< type of the color arrray
	ColorArray m_colors = { ///< contains all colors of the game.
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
	/**
	 * check if the provided color is valid.
	 */
	[[nodiscard]] bool CheckValidColor(Color& color);

	/**
	 * returns all colors.
	 */
	[[nodiscard]] ColorArray GetColors() const;
};
