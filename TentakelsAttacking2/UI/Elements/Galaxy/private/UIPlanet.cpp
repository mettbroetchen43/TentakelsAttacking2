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
	:UIGalaxyElement{ focusID, ID, { 0.015f, 0.025f }, player, pos, resolution, colliderPos }, m_planet{ planet } {
	
	AppContext_ty_c appContext{ AppContext::GetInstance() };
	auto const textSize{ MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		m_stringID.c_str(),
		m_collider.height,
		0.0f
	) };

	m_renderOffset = {
		(m_collider.width  - textSize.x) / 2,
		(m_collider.height - textSize.y) / 2
	};

	UpdateHoverText();
}

void UIPlanet::UpdateHoverText() {
	std::string const position{ "X: " + std::to_string(m_planet->GetPos().x) + ", Y: " + std::to_string(m_planet->GetPos().y) };

	std::string hover{ };
	if (m_planet->IsDiscovered()) {
		std::string const text_1{m_currentPlayer.GetName() + " | " + position + " |"};
		std::string const text_2{std::to_string(m_planet->GetShipCount())};
		hover = { AppContext::GetInstance().languageManager.Text("ui_planet_hover", text_1, text_2)};
	}
	else {
		hover = { m_currentPlayer.GetName() + " | " + position };
	}
	m_hover.SetText(hover);
}

void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

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
void UIPlanet::Render(AppContext_ty_c appContext) {
	DrawCircle(
		static_cast<int>(m_collider.x + m_collider.width / 2),
		static_cast<int>(m_collider.y + m_collider.height / 2),
		m_collider.width / 2,
		BLACK
	);

	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_stringID.c_str(),
		{ m_collider.x + m_renderOffset.x, m_collider.y  + m_renderOffset.y },
		m_collider.height,
		0.0f,
		m_color
	);
}
