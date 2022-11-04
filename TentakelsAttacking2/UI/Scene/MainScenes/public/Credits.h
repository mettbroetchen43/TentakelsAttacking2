//
// Purpur Tentakel
// 04.11.2022
//

#pragma once
#include "Scene.h"

class CreditsScene : public Scene {
private:
	Vector2 m_resolution;

	void Initialize(Vector2 resolution);

public:
	CreditsScene(Vector2 resolution);
};