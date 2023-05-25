//
// Purpur Tentakel
// 16.02.2022
//

#include "TargetPoint.h"
#include "HPrint.h"


bool TargetPoint::IsTargetPoint() const {
    return true;
}

void TargetPoint::Update(Galaxy const*) {
    Print("Updated TargetPoint. Nothing Happens", PrintType::DEBUG);
}
