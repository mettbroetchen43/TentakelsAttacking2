//
// PurpurTentakel
// 04.06.23
//

#include "HFightResult.h"

unsigned int HFightResult::GetDefenderID() const {
    return m_defenderID;
}
unsigned int HFightResult::GetAttackerID() const {
    return m_attackerID;
}
HFightResult::rounds_ty HFightResult::GetRounds() const {
    return m_rounds;
}
