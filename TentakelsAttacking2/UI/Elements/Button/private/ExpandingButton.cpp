//
// Purpur Tentakel
// 16.07.2023
//

#include "ExpandingButton.h"
#include "ClassicButton.h"
#include "ToggleButton.h"
#include "HPrint.h"

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

void ExpandingButton::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	m_mainButton->CheckAndUpdate(mousePosition, appContext);
	
	if (not CheckCollisionPointRec(mousePosition, m_collider)) {
		m_isExpanded = false;
		m_mainButton->SetToggleButton(m_isExpanded);
		HandleCollapse();
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
