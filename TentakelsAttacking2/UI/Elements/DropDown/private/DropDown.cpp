//
// Purpur Tentakel
// 01.12.2022
//

#include "DropDown.h"
#include "DropDownElement.h"

void DropDown::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    bool pressed = CheckCollisionPointRec(mousePosition, m_collider)
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (m_isFouldout) {
        if (pressed) {
            m_isEnabled = false;
        }



        for (auto e : m_dropDownElements) {
            if (e->IsEnabled()) {
                e->CheckAndUpdate(mousePosition, appContext);
            }
        }
    }
    else {

    }
}

bool DropDown::IsEnabled() const {
    return m_isEnabled;
}
void DropDown::SetEnabled(bool isEnabled) {
    m_isEnabled = isEnabled;
}

Rectangle DropDown::GetCollider() const {
    return m_collider;
}

DropDown::DropDown(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, unsigned int focusID,
    std::vector<std::string const> const& elements)
    : UIElement(pos, size, alignment, resolution), Focusable(focusID) {

    Initialize(elements);
}