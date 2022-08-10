//
// PurpurTentakel
// 08.08.22
//

#pragma once
#include "SpaceObject.h"
#include "GroupTarget.h"
#include <memory>

class Fleet : public SpaceObject {
private:
	std::shared_ptr<GroupTarget> m_target;
public:
	Fleet(int id, double x, double y, int ships, std::weak_ptr<Player> player, GroupTarget& target);

	void Move(Galaxy const& galaxy);

	void PreUpdate(Galaxy const& galaxy) override;
	void Update(Galaxy const& galaxy) override;
	void PostUpdate(Galaxy const& galaxy) override;

	[[nodiscard]] std::string ToString() const override;
};