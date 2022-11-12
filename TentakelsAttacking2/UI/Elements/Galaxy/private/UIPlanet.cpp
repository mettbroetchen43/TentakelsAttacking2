//
// Purpur Tentakel
// 09.11.2022
//

#include "UIPlanet.h"
#include "AppContext.h"

UIPlanet::UIPlanet(unsigned int focusID, unsigned int ID, Vector2 pos, Color color,
	Vector2 coliderPos, Vector2 resolution)
	:Focusable(focusID), UIElement(pos, { 0.01f,0.02f }, Alignment::MID_MID),m_ID(ID),
	m_color(color), m_coliderPos(coliderPos) {
	m_colider = GetAlignedCollider(m_pos, m_size, m_alignment, resolution);
	m_stringID = std::to_string(m_ID);
}

void UIPlanet::UpdatePosition(Rectangle newColider) {
	m_colider.x = newColider.x + newColider.width * m_coliderPos.x;
	m_colider.y = newColider.y + newColider.height * m_coliderPos.y;
}

void UIPlanet::SetOnClick(std::function<void()> onClick) {
	m_onClick = onClick;
}

void UIPlanet::UpdateColider(Vector2 resolution) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y,
	};
}

void UIPlanet::SetColor(Color color) {
	m_color = color;
}
Color UIPlanet::GetColor() const {
	return m_color;
}

void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {}
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
void UIPlanet::Resize(Vector2 resolution, AppContext const& appContext) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y,
	};
}

bool UIPlanet::IsEnabled() const {
	return m_isEnabled;
}
void UIPlanet::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
}

Rectangle UIPlanet::GetCollider() const {
	return m_colider;
}
