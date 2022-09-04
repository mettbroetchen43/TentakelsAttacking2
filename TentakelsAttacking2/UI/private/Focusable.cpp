//
// Purpur Tentakel
// 04.09.2022
//

#include "Focusable.h"
#include "AppContext.h"
#include "Events.h"

Focusable::Focusable(unsigned int ID)
	: m_focusID(ID) {
	AppContext& appContext = AppContext::GetInstance();
	auto event = NewFocusEvent(this);
	appContext.eventManager.InvokeEvent(event);
}
Focusable::~Focusable() {
	AppContext& appContext = AppContext::GetInstance();
	auto event = DeleteFocusEvent(this);
	appContext.eventManager.InvokeEvent(event);
}

bool Focusable::IsFocused() const {
	return m_isFocus;
}
void Focusable::SetFocus(bool focus) {
	m_isFocus = focus;
}
unsigned int Focusable::GetFocusID() const {
	return m_focusID;
}
