//
// Purpur Tentakel
// 01.12.2022
//

#include "DropDown.h"
#include "DropDownElement.h"
#include "HTextProcessing.h"
#include "HInput.h"
#include "HFocusEvents.h"
#include "UIEvents.hpp"
#include "AppContext.h"
#include <algorithm>



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
        entry->SetOnClick([this](unsigned int ID) {
            this->OnElementClick(ID);
            });
        entry->SetEnabled(false);
        m_dropDownElements.push_back(entry);
        ++startFocusID;
        y += height;

        if (i == 0) {
            SetCurrentElement(entry);
        }
    }
}

void DropDown::OnElementClick(unsigned int ID) {
    SetCurrentElementByID(ID);
}

void DropDown::SetCurrentElement(std::shared_ptr<DropDownElement> element) {
    m_currentElement = element;

    m_currentElementText = element->GetText();
    StripString(m_currentElementText);
    m_fontSize = GetElementTextHeight(
        m_size,
        m_resolution.y
    );
    m_currentElementText = GetPritableTextInColider(
        m_currentElementText,
        m_fontSize,
        m_collider,
        AppContext::GetInstance()
    );

    m_textPosition = {
        m_collider.x + 5.0f,
        m_collider.y + (m_collider.height - m_fontSize) / 2
    };

    m_onSave(element->GetID());
}

void DropDown::ToggleFoldedOut() {

    AppContext& appContext = AppContext::GetInstance();

    m_isFouldout = !m_isFouldout;

    appContext.eventManager.InvokeEvent(PlaySoundEvent(SoundType::CLICKED_PRESS_STD));

    if (m_isFouldout) {
        m_arrowTexture = appContext.assetManager.GetTexture(AssetType::ARROW_DOWN);
        AddFocusLayer();
        for (auto e : m_dropDownElements) {
            AddFocusElement(e.get());
        }
        CheckAndSetElementsEnabled();
    }
    else {
        m_arrowTexture = appContext.assetManager.GetTexture(AssetType::ARROW_UP);
        DeleteFocusLayer();
    }
}

Rectangle DropDown::GetTemporaryCollider(Rectangle collider) const {

    return GetCollisionRec(m_dropDownCollider, collider);
}

void DropDown::CheckAndSetElementsEnabled() {
    for (auto e : m_dropDownElements) {
        bool overlap = CheckCollisionRecs(m_dropDownCollider, e->GetCollider());
        e->SetEnabled(overlap);
    }
}

void DropDown::Scroll(float wheel) {

    if (!m_isScolling) { return; }

    for (auto e : m_dropDownElements) {
        Vector2 pos = e->GetPosition();
        pos.y +=  0.025f * wheel;
        e->SetPositionUnalligned(pos);
    }
    CheckAndSetElementsEnabled();
    ClampScrolling();
}
void DropDown::ClampScrolling() {

    float offset = 0.0f;
    auto element = m_dropDownElements.front();
    float dropDownValue = m_dropDownCollider.y;
    float elementValue = element->GetCollider().y;
    if (dropDownValue < elementValue) {
        offset = dropDownValue - elementValue;
    }

    element = m_dropDownElements.back();
    dropDownValue  = m_dropDownCollider.y + m_dropDownCollider.height;
    elementValue = element->GetCollider().y + element->GetCollider().height;
    if (dropDownValue > elementValue) {
        offset = dropDownValue - elementValue;
    }

    if (offset == 0.0f) { return; }

    for (auto e : m_dropDownElements) {
        Rectangle col = e->GetCollider();
        col.y += offset;
        e->SetCollider(col);
    }
}
void DropDown::CheckIfScolling() {
    float sum = 0;

    for (auto e : m_dropDownElements) {
        sum += e->GetCollider().height;
        if (m_dropDownCollider.height < sum) { m_isScolling = true; return; }
    }

    m_isScolling = sum > m_dropDownCollider.height;
}

DropDown::DropDown(Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution, float dropDownHeight,
    unsigned int focusID, unsigned int startElementFocusID, std::vector<std::string> const& elements)
    : UIElement(pos, size, alignment, resolution), Focusable(focusID), m_dropDownHeight(dropDownHeight) {



    m_arrowTexture = AppContext::GetInstance().assetManager.GetTexture(AssetType::ARROW_UP);
    m_arrowTextureRec = {
        0.0f,
        0.0f,
        static_cast<float>(m_arrowTexture->width),
        static_cast<float>(m_arrowTexture->height)
    };
    m_arrowCollider = {
        m_collider.x + m_collider.width - m_collider.height,
        m_collider.y,
        m_collider.height,
        m_collider.height
    };

    m_dropDownCollider = {
    m_collider.x,
    m_collider.y + m_collider.height,
    m_collider.width - m_arrowCollider.width,
    m_resolution.y * m_dropDownHeight
    };

    m_collider.width -= m_arrowCollider.width;
    UpdateColiderReverse();

    Initialize(elements, startElementFocusID);
}

std::shared_ptr<DropDownElement> DropDown::GetCurrentElement() const {

    return m_currentElement;
}

bool DropDown::SetCurrentElementByID(unsigned int ID) {
    
    for (auto e : m_dropDownElements) {
        if (e->GetID() == ID) {
            SetCurrentElement(e);
            if ( m_isFouldout ) {
                ToggleFoldedOut ( );
            }
            return true;
        }
    }
    return false;
}

void DropDown::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    bool hover = (CheckCollisionPointRec(mousePosition, m_collider)
        || CheckCollisionPointRec(mousePosition, m_arrowCollider));

    bool first = false;
    if (hover) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ToggleFoldedOut();
            first = true;
        }
    }
    if (IsFocused()) {
        if (IsConfirmInputPressed() && !IsNestedFocus() && !m_isFouldout) {
            ToggleFoldedOut();
            first = true;
        }
        if (IsBackInputPressed() && m_isFouldout) {
            ToggleFoldedOut();
            first = true;
        }
    }

    if (m_isFouldout) {
        float wheel = GetMouseWheelMove();
        if (wheel != 0.0f) {
            CheckIfScolling();
            Scroll(wheel);
        }
    }

    if (m_isFouldout && !first) {
        for (auto e : m_dropDownElements) {
            e->CheckAndUpdate(mousePosition, appContext);
        }
    }
}
void DropDown::Render(AppContext const& appContext) {
    DrawRectangleLinesEx(
        m_collider,
        2.0f,
        WHITE
    );

    if (m_currentElement) {
        DrawTextPro(
            *(appContext.assetManager.GetFont()),
            m_currentElementText.c_str(),
            m_textPosition,
            { 0.0f,0.0f },
            0.0f,
            m_fontSize,
            0.0f,
            WHITE
        );
    }

    DrawTexturePro(
        *m_arrowTexture,
        m_arrowTextureRec,
        m_arrowCollider,
        { 0.0f,0.0f },
        0.0f,
        WHITE
    );

    if (m_isFouldout) {

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

void DropDown::SetOnSave(std::function<void(unsigned int)> onSave) {
    m_onSave = onSave;
}
