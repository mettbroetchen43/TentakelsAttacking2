//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include <string>
#include <raylib.h>

struct AppContext;
enum class Alignment;

/**
 * replace a space thru an \n so that the text will break while dispaying.
 */
void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext const& appContext);

/**
 * returns the text absoluteHeight based of the parent relativeSize.
 */
[[nodiscard]] float GetElementTextHeight(Vector2 const& relativeSize, float absoluteHeight);

/**
 * modifies the string so it fits into a colider.
 * adds indigators(dots) if the string is modified.
 */
[[nodiscard]] std::string GetPritableTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
/**
 * modifies the string so it fits into a colider.
 * adds indigators(dots) if the string is modified.
 */
[[nodiscard]] std::string GetPritablePlaceholderTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);

/**
 * removes whitespace from the beginning and the end of a string.
 */
void StripString(std::string& toStrip);

/**
 * modifyes a string so it gets vertical aligned
 */
[[nodiscard]] Vector2 GetVerticalAlignedTextPosition(std::string const& text,
	float fontSize, Rectangle colider, Alignment alignment);
/**
 * modifyes a string so it gets horisontal aligned
 */
[[nodiscard]] std::string GetHorisontalAlignedText(std::string const& text,
	Rectangle colider, float fontSize, Alignment alignment);
