//
// Purpur Tentakel
// 09.11.2022
//

#include "UIPlanet.h"
#include "HInput.h"
#include "AppContext.h"
#include "HPrint.h"

void UIPlanet::SetHoverTextPosition(Vector2 mousePosition) {

	Rectangle currentCollider = m_hoverText->GetCollider();
	
	currentCollider.x = mousePosition.x + 2.0f;
	currentCollider.y = mousePosition.y - currentCollider.height - 2.0f;

	m_hoverText->SetCollider(currentCollider);
}

void UIPlanet::SetHoverTextDimension() {

	AppContext& appContext = AppContext::GetInstance();
	float newOffset = 5.0f;

	Vector2 dimension = MeasureTextEx(
		*(appContext.assetManager.GetFont()),
		m_currentPlayer.name.c_str(),
		m_hoverText->GetRelativeTextHeight(),
		0.0f
	);

	Rectangle currentCollider = m_hoverText->GetCollider();
	float offsetX = currentCollider.width - dimension.x;
	if (offsetX < 0) { offsetX = 0; }
	float offsetY = currentCollider.height - dimension.y;
	if (offsetY < 0) { offsetY = 0; }

	currentCollider.width = dimension.x + newOffset;
	currentCollider.height = dimension.y + newOffset;
	currentCollider.x = currentCollider.x + offsetX - newOffset / 2;
	currentCollider.y = currentCollider.y - offsetY + newOffset / 2;

	m_hoverText->SetCollider(currentCollider);
}

UIPlanet::UIPlanet(unsigned int focusID, unsigned int ID, PlayerData player, Vector2 pos, Vector2 resolution,
	Vector2 coliderPos)
	:Focusable(focusID), UIElement(pos, { 0.01f,0.02f }, Alignment::MID_MID, resolution)
	, m_ID(ID), m_currentPlayer(player), m_coliderPos(coliderPos) {

	m_hoverTexture = AppContext::GetInstance().assetManager.GetTexture(AssetType::GREY);
	m_hoverTextureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_hoverTexture->width),
		static_cast<float>(m_hoverTexture->height)
	};

	m_color = m_currentPlayer.color;
	m_stringID = std::to_string(m_ID);

	m_hoverText = std::make_unique<Text>(
		GetElementPosition(m_pos, m_size, 0.0f, 0.0f),
		GetElementSize(m_size, 0.0f, 0.0f),
		Alignment::BOTTOM_LEFT,
		resolution,
		Alignment::MID_MID,
		0.03f,
		player.name
		);
	m_hoverText->RenderRectangle(true);
	SetHoverTextDimension();

	auto currentCollider = m_hoverText->GetCollider();
	currentCollider.y -= currentCollider.height;
	m_hoverText->SetCollider(currentCollider);
}

void UIPlanet::UpdatePosition(Rectangle newColider) {
	m_collider.x = newColider.x + newColider.width * m_coliderPos.x;
	m_collider.y = newColider.y + newColider.height * m_coliderPos.y;
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

void UIPlanet::CheckAndUpdate(Vector2 const& mousePosition, AppContext const& appContext) {

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

	if (m_renderHover) {
		SetHoverTextPosition(mousePosition);
	}

	if (IsFocused() && IsConfirmInputPressed()) {
		m_onClick(this);
	}
}
void UIPlanet::Render(AppContext const& appContext) {
	DrawTextEx(
		*(appContext.assetManager.GetFont()),
		m_stringID.c_str(),
		{ m_collider.x, m_collider.y },
		m_collider.height,
		0.0f,
		m_currentPlayer.color
	);

	if (m_renderHover && m_currentPlayer.ID != 0) {

		DrawTexturePro(
			*m_hoverTexture,
			m_hoverTextureRec,
			m_hoverText->GetCollider(),
			{ 0.0f,0.0f },
			0.0f,
			WHITE
		);

		m_hoverText->Render(appContext);
	}

	/*DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);*/
}
void UIPlanet::Resize(Vector2 resolution, AppContext const& appContext) {

	m_hoverText->Resize(resolution, appContext);
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
