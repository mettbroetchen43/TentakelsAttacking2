//
// PurpurTentakel
// 08.08.22
//

#pragma once
#include "SpaceObject.h"
#include "GroupTarget.h"
#include <memory>

class Player;

class Fleet : public SpaceObject {
private:
	std::shared_ptr<GroupTarget*> m_target;
	int m_ships;
	int m_index;
	Player const* m_player;
public:
	Fleet(double x, double y, int ships, int index, Player const* player, GroupTarget& target);

	void Move(GameManager const& gameManager);

	void PreUpdate(GameManager const& gameManager) override;
	void Update(GameManager const& gameManager) override;
	void PostUpdate(GameManager const& gameManager) override;

	void Display() const override;

	void operator+=(int ships);
	void operator-=(int ships);
	[[nodiscard]] bool operator==(Fleet const& other);
};