//
// Purpur Tentakel
// 25.09.2022
//

#pragma once
#include <string>
#include <raylib.h>

struct AppContext;

void BreakText(std::string& toBreak, float fontSize, float length,
	AppContext const& appContext);

[[nodiscard]] float GetElementTextHight(Vector2 const& size, float height);

[[nodiscard]] std::string GetPritableTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
[[nodiscard]] std::string GetPritablePlaceholderTextInColider(std::string const& text,
	float fontSize, Rectangle colider, AppContext const& appContext);
