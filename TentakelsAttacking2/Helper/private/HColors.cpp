//
// Purpur Tentakel
// 20.10.2022
//

#include "HColors.h"
#include "UIEvents.hpp"
#include "HGeneral.h"

bool Colors::CheckValidColor(Color& color) {
	return std::find(m_colors.begin(), m_colors.end(), color)
		== m_colors.end();
}

Colors::ColorArray Colors::GetColors() const {
    return m_colors;
}
