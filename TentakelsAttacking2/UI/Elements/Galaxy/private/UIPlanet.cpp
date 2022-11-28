//
// Purpur Tentakel
// 09.11.2022
//

#include "UIPlanet.h"
#include "HInput.h"
#include "AppContext.h"

UIPlanet::UIPlanet(unsigned int focusID, unsigned int ID, Vector2 pos, Vector2 resolution,
	Color color, Vector2 coliderPos)
	:Focusable(focusID), UIElement(pos, { 0.01f,0.02f }, Alignment::MID_MID, resolution)
	,m_ID(ID), m_color(color), m_coliderPos(coliderPos) {
	m_stringID = std::to_string(m_ID);
}

void UIPlanet::UpdatePosition(Rectangle newColider) {
	m_colider.x = newColider.x + newColider.width * m_coliderPos.x;
	m_colider.y = newColider.y + newColider.height * m_coliderPos.y;
}

void UIPlanet::SetOnClick(std::function<void(UIPlanet*)> onClick) {
	m_onClick = onClick;
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

void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			m_onClick(this);
		}
	}
	if (IsFocused() && IsConfirmInputPressed()) {
		m_onClick(this);
	}
}
void UIPlanet::Render(AppContext const& appContext) {
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_stringID.c_str(),
		{ m_colider.x, m_colider.y },
		m_colider.height,
		0.0f,
		m_color
	);

	/*DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);*/
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
