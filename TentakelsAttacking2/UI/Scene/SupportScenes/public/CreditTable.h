//
// Purpur Tentakel
// 05.11.2022
//

#pragma once
#include "Scene.h"

class CreditTableScene : public Scene {
private:
	void Initialize(Vector2 resolution, int rows, unsigned int focusID, std::string const& headline);

public:
	CreditTableScene(unsigned int focusID, Vector2 pos, Vector2 size, Alignment alignment,
		int rows, std::string const& headline, Vector2 resolution);
};