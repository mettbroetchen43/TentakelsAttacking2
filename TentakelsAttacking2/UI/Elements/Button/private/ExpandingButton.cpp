//
// Purpur Tentakel
// 16.07.2023
//

#include "AppContext.h"
#include "ExpandingButton.h"
#include "ClassicButton.h"
#include "ToggleButton.h"
#include "UIEvents.hpp"
#include "HPrint.h"
#include "HInput.h"

void ExpandingButton::Initialize(int focusID, std::string const& btnText) {
	AppContext_ty_c appContext{ AppContext::GetInstance() };

	m_mainButton = std::make_shared<ToggleButton>(
		focusID,
		m_pos,
		m_size,
		Alignment::DEFAULT,
		m_resolution,
		btnText,
		SoundType::CLICKED_RELEASE_STD
	);
	m_mainButton->SetOnToggle([this](bool toggle, bool keyInput){
			this->HandleExpandChance(toggle, keyInput);
		}
	);

	NewFocusElementEvent const event{ m_mainButton.get() };
	appContext.eventManager.InvokeEvent(event);
}

void ExpandingButton::HandleExpandChance(bool expanding, bool keyInput) {
	m_wasKeyInput = keyInput;
	if (expanding) {
		HandleExpand();
	}
	else {
		HandleCollapse();
	}
}
void ExpandingButton::HandleExpand() {
	if (m_isExpanded) { return; }

	m_isExpanded = true;

	for (auto const& [btn, enabled, pos] : m_buttons){
		btn->SetEnabled(enabled);
		btn->MoveToPositionAsymptotic(pos, m_expandingSpeed);
	}
}
void ExpandingButton::HandleCollapse() {
	if (not m_isExpanded) { return; }

	m_isExpanded = false;
	for (auto const& [btn, _, __] : m_buttons){
		btn->SetEnabled(false);
		btn->MoveToPositionAsymptotic(m_mainButton->GetPosition(), m_expandingSpeed);
	}
}

bool ExpandingButton::IsBtnMoving() const {
	for (auto const& btn : m_buttons) {
		if (btn.btn->IsMoving()) {
			return true;
		}
	}
	return false;
}

ExpandingButton::ExpandingButton(int focusID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Direction direction, float spacing, float expandingSpeed, std::string const& btnText)
	: UIElement{ pos, size, alignment, resolution }, m_direction{ direction }, m_spacing{ spacing }, m_expandingSpeed{ expandingSpeed } {
	
	Initialize(focusID, btnText);
}

void ExpandingButton::Add(ClassicButton_ty btn, bool enabled) {
	m_buttons.emplace_back(btn, enabled, btn->GetPosition());
	NewFocusElementEvent const event{ btn.get() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void ExpandingButton::Remove(ClassicButton_ty btn) {
	DeleteFocusElementEvent const event{ btn.get() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	std::erase_if(m_buttons, [btn](Btn current) { return btn == current.btn; });
}
void ExpandingButton::Remove(int ind) {
	if (ind >= m_buttons.size()) { throw std::runtime_error("index out of range"); }

	auto const& btn{ m_buttons.at(ind) };
	DeleteFocusElementEvent const event{ btn.btn.get() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	m_buttons.erase(m_buttons.begin() + ind);
}

void ExpandingButton::SetDirection(Direction direction) {
	m_direction = direction;
}
ExpandingButton::Direction ExpandingButton::GetDirection() const {
	return m_direction;
}

void ExpandingButton::Update() {
	auto position{ m_mainButton->GetPosition() };
	auto const increse{ [&](bool first){
			float const offset{ first ? 2 * m_spacing : m_spacing };

			switch (m_direction)	 {
				case ExpandingButton::LEFT:
					position.x -= offset + m_mainButton->GetSize().x;
					break;

				case ExpandingButton::DOWN:
					position.y += offset + m_mainButton->GetSize().y;
					break;

				case ExpandingButton::RIGHT:
					position.x += offset + m_mainButton->GetSize().x;
					break;

				case ExpandingButton::UP:
					position.y -= offset + m_mainButton->GetSize().y;
					break;
			}
		}
	};

	for (int i = 0; i < m_buttons.size(); ++i) {
		auto& btn{ m_buttons.at(i) };
		increse(i == 0);
		btn.btn->SetEnabled(m_isExpanded ? btn.enabled : false);
		btn.btn->SetSize(m_mainButton->GetSize());
		btn.pos = position;
		btn.btn->SetPosition(m_isExpanded ? btn.pos : m_mainButton->GetPosition());
	}

	UpdateCollider();
}
void ExpandingButton::UpdateCollider() {
	if (m_buttons.empty()){
		SetCollider(m_mainButton->GetCollider());
		return;
	}

	auto defaultCollider{ m_mainButton->GetCollider() };
	Vector2 extraCollider{ m_spacing * m_resolution.x, m_spacing * m_resolution.y };
	for (auto const& btn : m_buttons) {
		extraCollider.x += m_spacing * m_resolution.x + btn.btn->GetCollider().width;
		extraCollider.y += m_spacing * m_resolution.y + btn.btn->GetCollider().height;
	}

	switch (m_direction) {
		case ExpandingButton::LEFT:
			defaultCollider.x -= extraCollider.x;
			defaultCollider.width += extraCollider.x;
			break;

		case ExpandingButton::DOWN:
			defaultCollider.height += extraCollider.y;
			break;

		case ExpandingButton::RIGHT:
			defaultCollider.width += extraCollider.x;
			break;

		case ExpandingButton::UP:
			defaultCollider.y -= extraCollider.y;
			defaultCollider.height += extraCollider.y;
			break;
	}

	Vector2 offset {
		defaultCollider.width * 0.01f,
		defaultCollider.height * 0.01f
	};
	offset.x = offset.x < 20.0f ? 20.0f : offset.x;
	offset.y = offset.y < 20.0f ? 20.0f : offset.y;
	defaultCollider.x -= offset.x / 2;
	defaultCollider.y -= offset.y / 2;
	defaultCollider.width += offset.x;
	defaultCollider.height += offset.y;

	SetCollider(defaultCollider);
}

void ExpandingButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	m_mainButton->CheckAndUpdate(mousePosition, appContext);
	
	if (m_isExpanded and not m_wasKeyInput and not m_delayedCollapse
		and not CheckCollisionPointRec(mousePosition, m_collider)) {
		m_delayedCollapse = true;
		m_collapseStartTime = GetTime();
	}
	else if (m_delayedCollapse and CheckCollisionPointRec(mousePosition, m_collider)) {
		m_delayedCollapse = false;
	}
	else if ( m_delayedCollapse and (GetTime() > m_collapseStartTime + m_delayedCollapseTime)) {
		m_delayedCollapse = false;
		HandleCollapse();
		m_mainButton->SetToggleButton(m_isExpanded);
	}

	if (m_isExpanded) {
		for (auto const& btn : m_buttons) {
			btn.btn->CheckAndUpdate(mousePosition, appContext);
		}
	}
	else if (IsBtnMoving()) {
		for (auto const& btn : m_buttons) {
			btn.btn->UpdateMove();
		}
	}
}
void ExpandingButton::Render(AppContext_ty_c appContext) {
	if (m_isExpanded or IsBtnMoving()) {
		for (auto const& btn : m_buttons) {
			btn.btn->Render(appContext);
		}
	}

	DrawRectangleLinesEx(m_collider, 2.0f, WHITE);

	m_mainButton->Render(appContext);
}
void ExpandingButton::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	UIElement::Resize(resolution, appContext);

	for (auto const& btn : m_buttons) {
		btn.btn->Resize(resolution,appContext);
	}
}
