//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "SpaceObject.h"

class Planet final : public SpaceObject {
private:
	int m_production;
	size_t m_maxShips;
public:
	Planet(int id, double x, double y, int ships, std::weak_ptr<Player> player, int production);
	
	void PreUpdate(Galaxy const& gameManager) override;
	void Update(Galaxy const& gameManager) override;
	void PostUpdate(Galaxy const& gameManager) override;
	[[nodiscard]] std::string ToString() const override;

	void ProduceShips();
	void ResetMaxShips();
};

