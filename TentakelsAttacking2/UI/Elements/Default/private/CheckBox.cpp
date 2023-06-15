//
// Purpur Tentakel
// 23.10.2022
//

#include "CheckBox.h"
#include "AppContext.h"
#include "UIEvents.hpp"
#include "HInput.h"

void CheckBox::Check(AppContext_ty_c appContext) {
	if (m_isChecked) {
		PlaySoundEvent const event{ SoundType::CLICKED_RELEASE_STD };
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		PlaySoundEvent const event{ SoundType::CLICKED_PRESS_STD };
		appContext.eventManager.InvokeEvent(event);
	}

	m_isChecked = !m_isChecked;

	m_onCheck(m_ID, m_isChecked);
}


CheckBox::CheckBox(unsigned int focusID, Vector2 pos, float height,
	Alignment alignment, Vector2 resolution, unsigned int checkBoxID)
	: UIElement{ pos, { 0.0f, height }, alignment, resolution }, Focusable{ focusID },
	m_ID{ checkBoxID } {

	m_size.x = resolution.y / resolution.x * m_size.y;
	UpdateCollider();

	AppContext_ty appContext{ AppContext::GetInstance() };
	m_texture = appContext.assetManager.GetTexture(AssetType::CHECK);
	m_textureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_texture->width),
		static_cast<float>(m_texture->height)
	};
}

void CheckBox::SetOnCheck(std::function<void(unsigned int, bool)> onCheck) {
	m_onCheck = onCheck;
}
unsigned int CheckBox::GetID() const {
	return m_ID;
}

void CheckBox::SetChecked(bool isChecked) {
	m_isChecked = isChecked;
}
bool CheckBox::IsChecked() const {
	return m_isChecked;
}

void CheckBox::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
}
bool CheckBox::IsEnabled() const {
	return m_isEnabled;
}

Rectangle CheckBox::GetCollider() const {
	return UIElement::GetCollider();
}

void CheckBox::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	bool check{ false };

	if (IsFocused()) {
		if (IsConfirmInputPressed()) {
			if (m_isEnabled) {
				check = true;
			}
			else {
				PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
				appContext.eventManager.InvokeEvent(event);
			}
		}
	}

	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		m_isHovered = true;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (m_isEnabled) {
				check = true;
			}
			else {
				PlaySoundEvent const event{ SoundType::CLICKED_DISABLED_STD };
				appContext.eventManager.InvokeEvent(event);
			}
		}
	}
	else {
		m_isHovered = false;
	}

	if (check) {
		Check(appContext);
	}
}
void CheckBox::Render([[maybe_unused]] AppContext_ty_c appContext) {
	DrawRectangleLinesEx(
		m_collider,
		3.0f,
		WHITE
	);

	if (m_isChecked) {
		DrawTexturePro(
			*m_texture,
			m_textureRec,
			m_collider,
			Vector2(0.0f, 0.0f),
			0.0f,
			WHITE
		);
	}

	if (!m_isEnabled) {
		DrawRectangleRec(
			m_collider,
			GREY_50
		);
	}

	if (m_isHovered) {
		DrawRectangleRec(
			m_collider,
			GREY_50
		);
	}
}

void CheckBox::Resize(Vector2 resolution, AppContext_ty_c appContext) {

	m_size.x = resolution.y / resolution.x * m_size.y;

	UIElement::Resize(resolution, appContext);
}
