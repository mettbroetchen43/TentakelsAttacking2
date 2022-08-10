//
// PurpurTentakel
// 10.08.22
//

#include "Player.h"

Player::Player(int id, std::string name, PlayerType playerType)
	: m_id(id), m_name(name),m_playerType(playerType) {}

std::string Player::GetName() const {
	return m_name;
}

bool Player::IsHumanPlayer() const {
	return m_playerType == PlayerType::HUMAN;
}

bool operator==(Player const& lhs, Player const& rhs) {
	return lhs.m_id == rhs.m_id;
}
