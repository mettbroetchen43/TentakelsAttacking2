//
// Purpur Tentakel
// 01.12.2022
//

#include "DropDownElement.h"
#include "HTextProcessing.h"
#include "HInput.h"
#include "AppContext.h"

void DropSownElement::CreateToRender() {
    m_toRender = m_text;
    StripString(m_toRender);
    m_fontSize = GetElementTextHeight(m_size, m_collider.height);
    m_toRender = GetPritableTextInColider(m_toRender, m_fontSize, m_collider, AppContext::GetInstance());

    m_textPosition = {
        m_collider.x + 5.0f,
        m_collider.y + (m_collider.height - m_fontSize) / 2
    };
}

DropSownElement::DropSownElement(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
    unsigned int focusID, unsigned int ID, std::string text)
    : UIElement(pos, size, alignment, resolution), Focusable(focusID), m_ID(ID), m_text(text) {

    m_grey50 = AppContext::GetInstance().assetManager.GetTexture(AssetType::GREY_50);
    m_textureRecGrey50 = {
        0.0f,
        0.0f,
        static_cast<float>(m_grey50->width),
        static_cast<float>(m_grey50->height)
    };

    CreateToRender();
}

void DropSownElement::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext){

    m_hover = CheckCollisionPointRec(mousePosition, m_collider);

    if (m_hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { m_onClick(m_ID); }

    if (IsFocused() && IsConfirmInputPressed()) { m_onClick(m_ID); }
}
void DropSownElement::Render(AppContext const& appContext) {

    if (m_hover) {
        DrawTexturePro(
            *m_grey50,
            m_textureRecGrey50,
            m_collider,
            { 0.0f,0.0f },
            0.0f,
            WHITE
        );
    }

    DrawRectangleLinesEx(
        m_collider,
        2.0f,
        WHITE
    );

    DrawTextPro(
        *(appContext.assetManager.GetFont()),
        m_toRender.c_str(),
        m_textPosition,
        { 0.0f,0.0f },
        0.0f,
        m_fontSize,
        0.0f,
        WHITE
    );
}

bool DropSownElement::IsEnabled() const {

    return m_isEnabled;
}
void DropSownElement::SetEnabled(bool isEnabled) {
    m_isEnabled = isEnabled;
}

void DropSownElement::SetText(std::string text) {
    m_text = text;
    CreateToRender();
}
void DropSownElement::SetOnClick(std::function<void(unsigned int)> onClick) {
    m_onClick = onClick;
}
Rectangle DropSownElement::GetCollider() const {
    return m_collider;
}
