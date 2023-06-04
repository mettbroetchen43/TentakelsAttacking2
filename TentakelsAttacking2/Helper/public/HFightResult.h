//
// PurpurTentakel
// 04.06.23
//

#include <vector>
#include <utility>

struct HFightResult final {
private:
	using rounds_ty = std::vector<std::pair<size_t, size_t>>;
	unsigned int m_defenderID;
	unsigned int m_attackerID;
	rounds_ty m_rounds;

public:
	[[nodiscard]] unsigned int GetDefenderID() const;
	[[nodiscard]] unsigned int GetAttackerID() const;
	[[nodiscard]] rounds_ty GetRounds() const;
};