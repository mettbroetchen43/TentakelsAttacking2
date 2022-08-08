//
// PurpurTentakel
// 08.08.22
//

class GameManager;

#pragma once
#include "Vec2.h"
#include <string>

class SpaceObject {
protected:
	Vec2<double> m_position;

public:
	SpaceObject(double x, double y);

	virtual void PreUpdate(GameManager const& gameManager) = 0;
	virtual void Update(GameManager const& gameManager) = 0;
	virtual void PostUpdate(GameManager const& gameManager) = 0;

	virtual void Display() const = 0;
	Vec2<double> GetPosition() const;
};

