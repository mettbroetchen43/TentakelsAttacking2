//
// Purpur Tentakel
// 16.07.2023
//

#include "ExpandingButton.h"
#include "ClassicButton.h"
#include "ToggleButton.h"
#include "HPrint.h"

void ExpandingButton::Initialize(int focusID, std::string const& btnText) {
	m_mainButton = std::make_shared<ToggleButton>(
		focusID,
		m_pos,
		m_size,
		Alignment::DEFAULT,
		m_resolution,
		btnText,
		SoundType::CLICKED_RELEASE_STD
	);
	m_mainButton->SetOnToggle([this](bool toggle){
			this->HandleExpandChance(toggle);
		}
	);
}

void ExpandingButton::HandleExpandChance(bool expanding) {
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

void ExpandingButton::SetDirection(Direction direction) {
	m_direction = direction;
}
ExpandingButton::Direction ExpandingButton::GetDirection() const {
	return m_direction;
}

void ExpandingButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	m_mainButton->CheckAndUpdate(mousePosition, appContext);
	
	if (not CheckCollisionPointRec(mousePosition, m_collider) and m_isExpanded) {
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
