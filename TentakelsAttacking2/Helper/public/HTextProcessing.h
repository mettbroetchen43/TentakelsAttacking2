//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include <string>
#include <raylib.h>

struct AppContext;
enum class Alignment;

void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext const& appContext);

[[nodiscard]] float GetElementTextHight(Vector2 const& size, float height);

[[nodiscard]] std::string GetPritableTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
[[nodiscard]] std::string GetPritablePlaceholderTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);

void StripString(std::string& toStrip);

[[nodiscard]] std::string GetAlignedText(std::string const& text,
	Rectangle colider, float fontSize, Alignment alignment);
