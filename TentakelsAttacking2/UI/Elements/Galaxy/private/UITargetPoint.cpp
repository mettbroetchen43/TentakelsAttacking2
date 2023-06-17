//
// Purpur Tentakel
// 09.11.2022
//

#include "UITargetPoint.h"
#include "TargetPoint.h"
#include "Player.h"
#include "HInput.h"

UITargetPoint::UITargetPoint(unsigned int focusID, unsigned int ID, PlayerData player, Vector2 pos,
	Vector2 resolution, Vector2 colliderPos, TargetPoint_ty_raw_c targetPoint)
	: UIGalaxyElement{ focusID, ID,{ 0.005f,0.01f },  player, pos, resolution, colliderPos }, m_targetPoint{ targetPoint } {
	UpdateHoverText();
}

void UITargetPoint::UpdateHoverText() {
	std::string const position{ "x: " + std::to_string(m_targetPoint->GetPos().x) + ", y: " + std::to_string(m_targetPoint->GetPos().y) };
	std::string const hover{ std::to_string(m_targetPoint->GetID()) + " | " + position + " | ships: " + std::to_string(m_targetPoint->GetShipCount())};
	m_hover.SetText(hover);
}

void UITargetPoint::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			m_onClick(this);
		}

		m_renderHover = true;
		UpdateHoverText();

	}
	else {
		m_renderHover = false;
	}

	if (m_renderHover) {
		m_hover.SetRenderHover(mousePosition, appContext);
	}

	if (IsFocused() && IsConfirmInputPressed()) {
		m_onClick(this);
	}
}
void UITargetPoint::Render(AppContext_ty_c) {
	DrawCircle(
		static_cast<int>(m_collider.x + m_collider.width / 2),
		static_cast<int>(m_collider.y + m_collider.height / 2),
		m_collider.width / 2,
		m_color
	);
}
