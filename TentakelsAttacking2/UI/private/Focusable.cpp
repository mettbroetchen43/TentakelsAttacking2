//
// Purpur Tentakel
// 04.09.2022
//

#include "Focusable.h"
#include "AppContext.h"
#include "HFocusEvents.h"
#include "UIEvents.hpp"
#include "HPrint.h"

Focusable::Focusable(unsigned int ID)
	: m_focusID(ID) { }
Focusable::~Focusable() {
	DeleteFocusElement(this);
}

bool Focusable::IsFocused() const {
	return m_isFocus;
}
void Focusable::SetFocus(bool focus) {
	m_isFocus = focus;
}
bool Focusable::IsNestedFocus() const {
	return m_isNestedFocus;
}
void Focusable::SetNestedFocus(bool nestedFocus) {
	m_isNestedFocus = nestedFocus;
}
unsigned int Focusable::GetFocusID() const {
	return m_focusID;
}

void Focusable::SetFocusID(unsigned int focusID) noexcept {
	if (focusID <= 0) { Print("provided focus ID is lower or eqal to zero.", PrintType::ERROR); return; }

	m_focusID = focusID;
}
