//
// Purpur Tentakel
// 23.07.2023
//

#include "ShipCountRing.h"

Color CountRing::GetDotColor() const {
    return m_dotColor;
}
void CountRing::SetDotColor(Color color) {
    m_dotColor = color;
}
Color CountRing::GetRingColor() const {
    return m_ringColor;
}
void CountRing::SetRingColor(Color color) {
    m_ringColor = color;
}
