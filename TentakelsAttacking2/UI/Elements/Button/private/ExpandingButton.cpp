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

	Print(
		PrintType::DEBUG,
		"expanding button is expanding. you just have to look closer"
	);
}
void ExpandingButton::HandleCollapse() {
	if (not m_isExpanded) { return; }

	m_isExpanded = false;

	Print(
		PrintType::DEBUG,
		"expanding button is collapsing. you just have to look closer"
	);
}

ExpandingButton::ExpandingButton(int focusID, Vector2 pos, Vector2 size, Alignment alignment, Vector2 resolution,
	Direction direction, float spacing, std::string const& btnText)
	: UIElement{ pos, size, alignment, resolution }, m_direction{ direction }, m_spacing{ spacing } {
	
	Initialize(focusID, btnText);
}

void ExpandingButton::Add(ClassicButton_ty btn) {
	m_buttons.push_back(btn);
	NewFocusElementEvent const event{ btn.get() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void ExpandingButton::Remove(ClassicButton_ty btn) {
	DeleteFocusElementEvent const event{ btn.get() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	std::erase_if(m_buttons, [btn](ClassicButton_ty current) { return btn == current; });
}
void ExpandingButton::Remove(int ind) {
	if (ind >= m_buttons.size()) { throw std::runtime_error("index out of range"); }

	auto const& btn{ m_buttons.at(ind) };
	DeleteFocusElementEvent const event{ btn.get() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);

	m_buttons.erase(m_buttons.begin() + ind);
}

void ExpandingButton::SetDirection(Direction direction) {
	m_direction = direction;
}
ExpandingButton::Direction ExpandingButton::GetDirection() const {
	return m_direction;
}

void ExpandingButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	m_mainButton->CheckAndUpdate(mousePosition, appContext);
	
	if (m_isExpanded and not m_wasKeyInput
		and not CheckCollisionPointRec(mousePosition, m_collider)) {
		HandleCollapse();
		m_mainButton->SetToggleButton(m_isExpanded);
	}

	if (m_isExpanded) {
		for (auto const& btn : m_buttons) {
			btn->CheckAndUpdate(mousePosition, appContext);
		}
	}
}
void ExpandingButton::Render(AppContext_ty_c appContext) {
	m_mainButton->Render(appContext);

	if (m_isExpanded) {
		for (auto const& btn : m_buttons) {
			btn->Render(appContext);
		}
	}
}
void ExpandingButton::Resize(Vector2 resolution, AppContext_ty_c appContext) {
	UIElement::Resize(resolution, appContext);

	for (auto const& btn : m_buttons) {
		btn->Resize(resolution,appContext);
	}
}
