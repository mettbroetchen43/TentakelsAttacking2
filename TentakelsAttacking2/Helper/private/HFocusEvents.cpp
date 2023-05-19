//
// Purpur Tentakel
// 23.10.2022
//

#include "HFocusEvents.h"
#include "AppContext.h"
#include "UIEvents.hpp"
#include "HFocusEvents.h"

void AddFocusLayer(bool isPopUp) {
	if (isPopUp) {
		auto const event{ NewFocusPopUpLayerEvent() };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto const event{ NewFocusLayerEvent() };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void DeleteFocusLayer(bool isPopUp) {
	if (isPopUp) {
		auto const event{ DeleteFocusPopUpLayerEvent() };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto const event{ DeleteFocusLayerEvent() };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

void AddFocusElement(Focusable* focusable, bool isPopUp) {
	if (isPopUp) {
		auto const event{ NewFocusPopUpElementEvent(focusable) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto const event{ NewFocusElementEvent(focusable) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
void DeleteFocusElement(Focusable* focusable, bool isPopUp) {
	if (isPopUp) {
		auto const event{ DeleteFocusPopUpElementEvent(focusable) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto const event{ DeleteFocusElementEvent(focusable) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}

void SelectNextFocusElement() {
	auto const event{ SelectNextFocusElementEvent() };
	AppContext::GetInstance().eventManager.InvokeEvent(event);
}
void SelectFocusElement(Focusable* focusable, bool isPopUp) {
	if (isPopUp) {
		auto const event{ SelectFocusPopUpElementEvent(focusable) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
	else {
		auto const event{ SelectFocusElementEvent(focusable) };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
	}
}
