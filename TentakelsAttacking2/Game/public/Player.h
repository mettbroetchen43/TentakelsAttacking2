//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "PlayerType.h"
#include <string>

class Player {
private:
	int m_id;
	PlayerType m_playerType;
	std::string m_name;
public:
	Player(int id, std::string name, PlayerType playerType);

	[[nodiscard]] std::string GetName() const;

	[[nodiscard]] bool IsHumanPlayer() const;

	friend bool operator== (Player const& lhs, Player const& rhs);
};

