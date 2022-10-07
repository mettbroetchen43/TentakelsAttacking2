//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include <string>

struct AppContext;
struct Rectangle;

void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext const& appContext);

[[nodiscard]] std::string GetPritableTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
[[nodiscard]] std::string GetPritablePlaceholderTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
