//
// Purpur Tentakel
// 16.06.2023
//

#include "UIFleet.h"
#include "Fleet.h"
#include "AppContext.h"

UIFleet::UIFleet(PlayerData player, Vector2 start, Vector2 end, Vector2 resolution, Vector2 relativeStart, Vector2 relativeEnd,
    Fleet_ty_raw_c fleet, std::function<bool(Vector2 const&)> isInGalaxyCollider)
    : UIElement{ start, { 0.0f,0.0f }, Alignment::MID_MID, resolution }, m_player{ player },
    m_relativeStart{ relativeStart }, m_relativeEnd{ relativeEnd }, m_fleet { fleet }, m_isInGalaxyCollider{ isInGalaxyCollider },
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

bool UIFleet::IsColliding(Vector2 const& mousePosition) const {
    if (not m_isInGalaxyCollider(mousePosition)) { return false; }

    auto const& lineStart{ m_line.GetStart() };
    auto const& lineEnd{ m_line.GetEnd() };
    Vector2 const start{
        lineStart.x * m_resolution.x,
        lineStart.y * m_resolution.y
    };
    Vector2 const end{
        lineEnd.x * m_resolution.x,
        lineEnd.y * m_resolution.y,
    };

    return CheckCollisionPointLine(mousePosition, start, end, 5);
}

void UIFleet::UpdateHoverText() {
    std::string const position{ "X: " + std::to_string(m_fleet->GetPos().x) + ", Y: " + std::to_string(m_fleet->GetPos().y) };
    std::string const text_1{ std::to_string(m_fleet->GetID()) + " | " + position + " |" };
    std::string const text_2{ std::to_string(m_fleet->GetShipCount())};
    m_hover.SetText(AppContext::GetInstance().languageManager.Text("ui_fleet_hover", text_1, text_2));
}
void UIFleet::UpdatePositions(Rectangle newCollider) {
    Vector2 const start{
        (newCollider.x + newCollider.width  * m_relativeStart.x) / m_resolution.x,
        (newCollider.y + newCollider.height * m_relativeStart.y) / m_resolution.y
    };
    Vector2 const end{
        (newCollider.x + newCollider.width  * m_relativeEnd.x) / m_resolution.x,
        (newCollider.y + newCollider.height * m_relativeEnd.y) / m_resolution.y
    };

    m_line.SetStart(start);
    m_line.SetEnd(end);
    m_line.Update();
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
