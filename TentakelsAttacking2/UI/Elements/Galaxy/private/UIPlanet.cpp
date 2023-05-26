//
// Purpur Tentakel
// 09.11.2022
//

#include "UIPlanet.h"
#include "HInput.h"
#include "AppContext.h"
#include "HPrint.h"

UIPlanet::UIPlanet(unsigned int focusID, unsigned int ID, PlayerData player, Vector2 pos, Vector2 resolution,
	Vector2 colliderPos)
	:Focusable{ focusID }, UIElement{ pos, { 0.01f,0.02f }, Alignment::MID_MID, resolution }
	, m_ID{ ID }, m_currentPlayer{ player }, m_colliderPos{ colliderPos }, m_color{ player.color }, m_stringID{ std::to_string(ID) },
	m_hover{
		0.03f,
		player.name,
		player.color,
		Vector2(0.01f,0.01f),
		resolution }
{ }

void UIPlanet::UpdatePosition(Rectangle newCollider) {
	m_collider.x = newCollider.x + newCollider.width * m_colliderPos.x;
	m_collider.y = newCollider.y + newCollider.height * m_colliderPos.y;
}

void UIPlanet::SetOnClick(std::function<void(UIPlanet*)> onClick) {
	m_onClick = onClick;
}

void UIPlanet::SetPlayer(PlayerData player) {
	m_currentPlayer = player;
	if (m_color != GRAY) {
		m_color = m_currentPlayer.color;
	}
}
PlayerData UIPlanet::GetPlayer() const {
	return m_currentPlayer;
}

void UIPlanet::SetColor(Color color) {
	m_color = color;
}
Color UIPlanet::GetColor() const {
	return m_color;
}

unsigned int UIPlanet::GetID() const {
	return m_ID;
}

bool UIPlanet::IsHover() const {
	return m_renderHover;
}

void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			m_onClick(this);
		}

		m_renderHover = true;
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

bool UIPlanet::IsEnabled() const {
	return m_isEnabled;
}
void UIPlanet::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
}

Rectangle UIPlanet::GetCollider() const {
	return UIElement::GetCollider();
}
