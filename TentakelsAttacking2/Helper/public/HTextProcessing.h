//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include "CustomRaylib.h"
#include <string>
#include <vector>

struct AppContext;
enum class Alignment;

/**
 * replace a space thru an \n so that the text will break while dispaying.
 */
void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext const& appContext);
/**
 * splits the string and returns a vector.
 */
[[nodiscard]] std::vector<std::string> BreakTextInVector(std::string const& toBreak, float fontSite,
	float length);

/**
 * returns the text absoluteHeight based of the parent relativeSize.
 */
[[nodiscard]] float GetElementTextHeight(Vector2 const& relativeSize, float absoluteHeight);

/**
 * modifies the string so it fits into a colider.
 * adds indigators(dots) if the string is modified.
 */
[[nodiscard]] std::string GetPrintableTextInCollider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
/**
 * modifies the string so it fits into a colider.
 * adds indigators(dots) if the string is modified.
 */
[[nodiscard]] std::string GetPrintablePlaceholderTextInCollider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);

/**
 * removes whitespace from the beginning and the end of a string.
 */
void StripString(std::string& toStrip);

/**
 * modifyes a string so it gets vertical aligned.
 */
[[nodiscard]] Vector2 GetVerticalAlignedTextPosition(std::string const& text,
	float fontSize, Rectangle colider, Alignment alignment);
/**
 * returns the vertical offset per line in a vector.
 */
[[nodiscard]] std::vector<float> GetVerticalAlignedOffset(std::vector<std::string> text,
	float fontSize, Rectangle colider, Alignment alignment);
/**
 * modifyes a string so it gets horisontal aligned.
 */
[[nodiscard]] std::string GetHorizontalAlignedText(std::string const& text,
	Rectangle colider, float fontSize, Alignment alignment);
/**
 * returns the horisintal offset per line in a vector.
 */
[[nodiscard]] std::vector<float> GetHorizontalAlignedOffset(std::vector<std::string> text,
	Rectangle colider, float fontSize, Alignment alignment);
