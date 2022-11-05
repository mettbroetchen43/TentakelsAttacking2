//
// Purpur Tentakel
// 05.11.2022
//

#pragma once
#include "Scene.h"

class CreditTableScene : public Scene {
private:
	void Initialize(Vector2 resolution, std::string const& headline,
		std::vector<std::string> const& entries, bool doubleColumn);

public:
	CreditTableScene(Vector2 pos, Vector2 size, Alignment alignment,
		std::string const& headline, std::vector<std::string> const& entries,
		bool doubleColumn, Vector2 resolution);
};