//
// Purpur Tentakel
// 09.11.2022
//

#include "UIPlanet.h"
#include "HInput.h"
#include "AppContext.h"
#include "Planet.h"

UIPlanet::UIPlanet(unsigned int focusID, unsigned int ID, PlayerData player, Vector2 pos, Vector2 resolution,
	Vector2 colliderPos, Planet_ty_raw_c planet)
	:UIGalaxyElement{ focusID, ID, player, pos, resolution, colliderPos }, m_planet{ planet } {
	
	UpdateHoverText();
}

void UIPlanet::UpdateHoverText() {
	std::string const hover{ m_currentPlayer.name + " | x: " + std::to_string(m_planet->GetPos().x) + " y: " + std::to_string(m_planet->GetPos().y) + " | ships: " + std::to_string(m_planet->GetShipCount()) };
	m_hover.SetText(hover);
}

void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			m_onClick(this);
		}
		
		if (m_planet->IsDiscovered()) {
			m_renderHover = true;
			UpdateHoverText();
		}
	}
	else {
		m_renderHover = false;
	}

	if (m_renderHover && m_currentPlayer.ID != 0) {
		m_hover.SetRenderHover(mousePosition, appContext);
	}

	if (IsFocused() && IsConfirmInputPressed()) {
		m_onClick(this);
	}
}
void UIPlanet::Render(AppContext_ty_c appContext) {
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_stringID.c_str(),
		{ m_collider.x, m_collider.y },
		m_collider.height,
		0.0f,
		m_color
	);
}
void UIPlanet::Resize(Vector2 resolution, AppContext_ty_c appContext) {

	m_hover.Resize(resolution, appContext);
	UIElement::Resize(resolution, appContext);
}
