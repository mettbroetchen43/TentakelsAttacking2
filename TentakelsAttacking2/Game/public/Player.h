//
// PurpurTentakel
// 10.08.22
//

#pragma once
#include "PlayerType.hpp"

class Player final {
private:
	unsigned int m_ID;
	PlayerType m_playerType;
public:
	Player(unsigned int ID, PlayerType playerType);

	[[nodiscard]] bool IsHumanPlayer() const;

	[[nodiscard]] unsigned int GetID() const;

	friend bool operator== (Player const& lhs, Player const& rhs);
};

