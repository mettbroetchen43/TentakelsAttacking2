//
// Purpur Tentakel
// 23.10.2022
//

#include "HFocusEvents.h"
#include "AppContext.h"
#include "UIEvents.hpp"

void AddFocusLayer(bool isPopUp) {
	if (isPopUp) {
		auto event = NewFocusPopUpLayerEvent();
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto event = NewFocusLayerEvent();
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void DeleteFocusLayer(bool isPopUp) {
	if (isPopUp) {
		auto event = DeleteFocusPopUpLayerEvent();
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto event = DeleteFocusLayerEvent();
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

void AddFocusElement(Focusable* focusable, bool isPopUp) {
	if (isPopUp) {
		auto event = NewFocusPopUpElementEvent(focusable);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto event = NewFocusElementEvent(focusable);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void DeleteFocusElement(Focusable* focusable, bool isPopUp) {
	if (isPopUp) {
		auto event = DeleteFocusPopUpElementEvent(focusable);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto event = DeleteFocusElementEvent(focusable);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

void SelectFocusElement(Focusable* focusable, bool isPopUp) {
	if (isPopUp) {
		auto event = SelectFocusPopUpElementEvent(focusable);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto event = SelectFocusElementEvent(focusable);
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
