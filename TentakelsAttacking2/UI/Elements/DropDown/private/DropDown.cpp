//
// Purpur Tentakel
// 01.12.2022
//

#include "DropDown.h"
#include "DropDownElement.h"
#include <algorithm>

void DropDown::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    for (auto e : m_dropDownElements) {
        e->CheckAndUpdate(mousePosition, appContext);
        
    }
}

void DropDown::Render(AppContext const& appContext) {
    DrawRectangleLinesEx(
        m_collider,
        2.0f,
        WHITE
    );

    BeginScissorMode(
        static_cast<int>(m_dropDownCollider.x),
        static_cast<int>(m_dropDownCollider.y),
        static_cast<int>(m_dropDownCollider.width),
        static_cast<int>(m_dropDownCollider.height)
    );

    for (auto e : m_dropDownElements) {
        e->Render(appContext);
    }

    EndScissorMode();
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

void DropDown::Initialize(std::vector<std::string> const& elements, unsigned int startFocusID) {

    float x = m_pos.x + m_size.x * 0.01f;
    float y = m_pos.y + m_size.y;
    float width = m_size.x * 0.98f;
    float height = m_size.y * 2 / 3;

    for (size_t i = 0; i < elements.size(); ++i) {
        auto entry = std::make_shared<DropDownElement>(
            Vector2(x, y),
            Vector2(width, height),
            Alignment::DEFAULT,
            m_resolution,
            startFocusID,
            static_cast<unsigned int>(i + 1),
            elements.at(i),
            [this](Rectangle collider) -> Rectangle {
                return this->GetTemporaryCollider(collider);
            }
        );
        entry->SetEnabled(false);
        m_dropDownElements.push_back(entry);
        ++startFocusID;
        y += height;

        if (i == 0) {
            m_currentElement = entry;
        }
    }
}

void DropDown::OnElementClick(unsigned int ID) {
    SetCurrentElementByID(ID);
}

Rectangle DropDown::GetTemporaryCollider(Rectangle collider) const {

    return GetCollisionRec(m_dropDownCollider, collider);
}

DropDown::DropDown(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, float dropDownHeight,
    unsigned int focusID, unsigned int startElementFocusID, std::vector<std::string> const& elements)
    : UIElement(pos, size, alignment, resolution), Focusable(focusID), m_dropDownHeight(dropDownHeight) {

    m_dropDownCollider = {
        m_collider.x,
        m_collider.y + m_collider.height,
        m_collider.width,
        m_resolution.y * m_dropDownHeight
    };

    Initialize(elements, startElementFocusID);
}

std::shared_ptr<DropDownElement> DropDown::GetCurrentElement() const {

    return m_currentElement;
}
bool DropDown::SetCurrentElementByID(unsigned int ID) {
    
    for (auto e : m_dropDownElements) {
        if (e->GetID() == ID) {
            m_currentElement = e;
            return true;
        }
    }
    return false;
}
