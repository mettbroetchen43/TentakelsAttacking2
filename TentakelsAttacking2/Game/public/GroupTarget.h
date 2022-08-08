//
// PurpurTentakel
// 08.08.22
//

#pragma once
#include "SpaceObject.h"

class GroupTarget: public SpaceObject {
private:

public:
	using SpaceObject::SpaceObject;

	void UpdatePosition(double x, double y);

	void PreUpdate(GameManager const& gameManager) override;
	void Update(GameManager const& gameManager) override;
	void PostUpdate(GameManager const& gameManager) override;

	void Display() const override;


};

