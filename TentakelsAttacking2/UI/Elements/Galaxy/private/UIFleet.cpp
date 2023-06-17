//
// Purpur Tentakel
// 16.06.2023
//

#include "UIFleet.h"
#include "Fleet.h"

bool UIFleet::IsColliding(Vector2 const& mousePosition) const {
    auto const& lineStart{ m_line.GetStart() };
    auto const& lineEnd  { m_line.GetEnd()   };
    Vector2 const start{
        lineStart.x * m_resolution.x,
        lineStart.y * m_resolution.y
    };
    Vector2 const end{
        lineEnd.x * m_resolution.x,
        lineEnd.y * m_resolution.y,
    };

    return CheckCollisionPointLine(mousePosition, start, end, 2);
}

UIFleet::UIFleet(PlayerData player, Vector2 start, Vector2 end, Vector2 resolution, Fleet_ty_raw_c fleet)
    : UIElement{ start, { 0.0f,0.0f }, Alignment::MID_MID, resolution }, m_player{ player }, m_fleet{ fleet },
    m_line{
        start,
        end,
        resolution,
        1.0f,
        player.color
    },
    m_hover{
        0.03f,
        "",
        player.color,
        Vector2(0.01f,0.01f),
        resolution
    } {
    UpdateHoverText();
}

void UIFleet::UpdateHoverText() {
    std::string const position{ "x: " + std::to_string(m_fleet->GetPos().x) + ", y: " + std::to_string(m_fleet->GetPos().y) };
    std::string const text{ std::to_string(m_fleet->GetID()) + " | " + position + " | ships: " + std::to_string(m_fleet->GetShipCount()) };
    m_hover.SetText(text);
}
void UIFleet::UpdatePositions(Vector2 start, Vector2 end) {
    m_line.SetStart(start);
    m_line.SetEnd(end);
}

void UIFleet::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    UIElement::CheckAndUpdate(mousePosition, appContext);

    if (IsColliding(mousePosition)) {
        UpdateHoverText();
        m_hover.SetRenderHover(mousePosition, appContext);
    }
}
void UIFleet::Render(AppContext_ty_c appContext) {
    m_line.Render(appContext);
}
void UIFleet::Resize(Vector2 resolution, AppContext_ty_c appContext) {
    UIElement::Resize(resolution, appContext);
    m_line.Resize(resolution, appContext);
    m_hover.Resize(resolution, appContext);
}
