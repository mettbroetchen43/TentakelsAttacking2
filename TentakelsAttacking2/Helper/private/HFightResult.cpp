//
// PurpurTentakel
// 04.06.23
//

#include "HFightResult.h"

HFightResult::HFightResult(unsigned int defenderID, unsigned int attackerID, rounds_ty rounds, bool valid)
    : m_defenderID{ defenderID }, m_attackerID{ attackerID }, m_rounds{ rounds }, m_valid{ valid } { }

unsigned int HFightResult::GetDefenderID() const {
    return m_defenderID;
}
unsigned int HFightResult::GetAttackerID() const {
    return m_attackerID;
}
HFightResult::rounds_ty HFightResult::GetRounds() const {
    return m_rounds;
}

bool HFightResult::IsValid() const {
    return m_valid;
}
