//
// PurpurTentakel
// 04.06.23
//

#include <vector>
#include <utility>
#pragma once

struct HFightResult final {
public:
	using rounds_ty = std::vector<std::pair<size_t, size_t>>;

	HFightResult(unsigned int defenderID, unsigned int attackerID, rounds_ty rounds, bool valid);

	[[nodiscard]] unsigned int GetDefenderID() const;
	[[nodiscard]] unsigned int GetAttackerID() const;
	[[nodiscard]] rounds_ty GetRounds() const;
	[[nodiscard]] bool IsValid() const;

private:
	unsigned int m_defenderID;
	unsigned int m_attackerID;
	rounds_ty m_rounds;
	bool m_valid;
};