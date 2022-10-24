//
// Purpur Tentakel
// 23.10.2022
//

#include "CheckBox.h"
#include "AppContext.h"
#include "UIEvents.hpp"
#include "HInput.h"

void CheckBox::Check(AppContext const& appContext) {
	if (m_isChecked) {
		auto event = PlaySoundEvent(SoundType::CLICKED_RELEASE_STD);
		appContext.eventManager.InvokeEvent(event);
	}
	else {
		auto event = PlaySoundEvent(SoundType::CLICKED_PRESS_STD);
		appContext.eventManager.InvokeEvent(event);
	}

	m_isChecked = !m_isChecked;

	m_onCheck(m_ID, m_isChecked);
}

CheckBox::CheckBox(unsigned int focusID, Vector2 pos, float height,
	Alignment alignment, unsigned int checkBoxID,
	Vector2 resolution)
	: UIElement(pos, { 0.0f, height }, alignment), Focusable(focusID),
	m_ID(checkBoxID) {

	m_size.x = resolution.y / resolution.x * m_size.y;
	m_colider = GetAlignedCollider(m_pos, m_size, alignment, resolution);

	AppContext& appCpntext = AppContext::GetInstance();
	m_texture = appCpntext.assetManager.GetTexture(AssetType::CHECK);
	m_textureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_texture->width),
		static_cast<float>(m_texture->height)
	};

	m_greyTexture = appCpntext.assetManager.GetTexture(AssetType::GREY_50);
	m_greyTextureRec = {
		0.0f,
		0.0f,
		static_cast<float>(m_greyTexture->width),
		static_cast<float>(m_greyTexture->height)
	};
}

void CheckBox::SetOnCheck(std::function<void(unsigned int, bool)> onCheck) {
	m_onCheck = onCheck;
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
	return m_colider;
}

void CheckBox::CheckAndUpdate(Vector2 const& mousePosition,
	AppContext const& appContext) {

	bool check = false;

	if (IsFocused()) {
		if (IsConfirmInputPressed()) {
			if (m_isEnabled) {
				check = true;
			}
			else {
				auto event = PlaySoundEvent(SoundType::CLICKED_DISABLED_STD);
				appContext.eventManager.InvokeEvent(event);
			}
		}
	}

	if (CheckCollisionPointRec(mousePosition, m_colider)) {
		m_isHovered = true;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if (m_isEnabled) {
				check = true;
			}
			else {
				auto event = PlaySoundEvent(SoundType::CLICKED_DISABLED_STD);
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
void CheckBox::Render([[maybe_unused]] AppContext const& appContext) {
	DrawRectangleLinesEx(
		m_colider,
		3.0f,
		WHITE
	);

	if (m_isChecked) {
		DrawTexturePro(
			*m_texture,
			m_textureRec,
			m_colider,
			Vector2(0.0f, 0.0f),
			0.0f,
			WHITE
		);
	}

	if (!m_isEnabled) {
		DrawTexturePro(
			*m_greyTexture,
			m_greyTextureRec,
			m_colider,
			Vector2(0.0f, 0.0f),
			0.0f,
			WHITE
		);
	}

	if (m_isHovered) {
		DrawTexturePro(
			*m_greyTexture,
			m_greyTextureRec,
			m_colider,
			Vector2(0.0f, 0.0f),
			0.0f,
			WHITE
		);
	}
}
void CheckBox::Resize(Vector2 resolution,
	[[maybe_unused]] AppContext const& appContext) {
	m_colider = {
		resolution.x * m_pos.x,
		resolution.y * m_pos.y,
		resolution.x * m_size.x,
		resolution.y * m_size.y
	};
}
