//
// Purpur Tentakel
// 04.09.2022
//

#include "Focus.h"
#include "Focusable.h"
#include "AppContext.h"
#include "UIEvents.hpp"
#include <stdexcept>

bool Focus::HasAnyEnabledElements() const {
	for (auto e : m_focus) {
		if (e->IsEnabled()) {
			return true;
		}
	}
	return false;
}

void Focus::UnfocusAllAtTopLayer() {
	for (auto focus : m_focus) {
		focus->SetFocus(false);
	}

	m_currentFocus = nullptr;
}
Focusable* Focus::GetFirstFocus() {
	Focusable* firstFocus = nullptr;
	bool hasAnyEnabledElements = HasAnyEnabledElements();

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements
			and !focus->IsEnabled()) {
				continue;
		}

		if (!firstFocus) {
			firstFocus = focus;
		}
		if (firstFocus->GetFocusID() > focus->GetFocusID()) {
			firstFocus = focus;
		}
	}

	return firstFocus;
}
Focusable* Focus::GetLastFocus() {
	Focusable* lastFocus = nullptr;
	bool hasAnyEnabledElements = HasAnyEnabledElements();

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements
			and !focus->IsEnabled()) {
				continue;
		}
		if (!lastFocus) {
			lastFocus = focus;
			continue;
		}
		if (lastFocus->GetFocusID() < focus->GetFocusID()) {
			lastFocus = focus;
		}
	}

	return lastFocus;
}
Focusable* Focus::GetNextFocus() {
	unsigned int currentID = m_currentFocus ? m_currentFocus->GetFocusID() : 0;
	Focusable* nextFocus = nullptr;
	bool hasAnyEnabledElements = HasAnyEnabledElements();

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements 
			and !focus->IsEnabled()) {
				continue;
		}
		if (focus->GetFocusID() > currentID) {
			if (!nextFocus) {
				nextFocus = focus;
				continue;
			}
			if (focus->GetFocusID() < nextFocus->GetFocusID()) {
				nextFocus = focus;
			}
		}
	}

	return nextFocus;
}
Focusable* Focus::GetPreviousFocus() {
	unsigned int currentID = m_currentFocus ? m_currentFocus->GetFocusID() 
		: static_cast<unsigned int>(m_focus.size());
	Focusable* previousFocus = nullptr;
	bool hasAnyEnabledElements = HasAnyEnabledElements();

	for (auto focus : m_focus) {
		if (hasAnyEnabledElements
			and !focus->IsEnabled()) {
				continue;
		}
		if (focus->GetFocusID() < currentID) {
			if (!previousFocus) {
				previousFocus = focus;
				continue;
			}
			if (focus->GetFocusID() > previousFocus->GetFocusID()) {
				previousFocus = focus;
			}
		}
	}

	return previousFocus;
}
void Focus::SetInitialFocus() {
	m_currentFocus = GetFirstFocus();
	if (m_currentFocus) {
		m_currentFocus->SetFocus(true);
	}
}
void Focus::SetNextFocus() {
	m_currentFocus->SetFocus(false);

	Focusable* nextFocus = GetNextFocus();
	if (!nextFocus) {
		nextFocus = GetFirstFocus();
	}

	m_currentFocus = nextFocus;
	m_currentFocus->SetFocus(true);
}
void Focus::SetPreviousFocus() {
	m_currentFocus->SetFocus(false);

	Focusable* previousFocus = GetPreviousFocus();
	if (!previousFocus) {
		previousFocus = GetLastFocus();
	}

	m_currentFocus = previousFocus;
	m_currentFocus->SetFocus(true);
}
void Focus::SetSpecificFocus(Focusable* focusable) {
	if (!IsExistingFocus(focusable)) { return; }

	if (m_currentFocus) {
		m_currentFocus->SetFocus(false);
	}
	m_currentFocus = focusable;
	m_currentFocus->SetFocus(true);
}
bool Focus::IsExistingFocus(Focusable* focusable) {
	for (auto focus : m_focus) {
		if (focus == focusable) {
			return true;
		}
	}
	return false;
}

void Focus::AddLayer() {
	m_lastFocus.push_back(m_currentFocus);
	m_focus.AddLayer();
	m_currentFocus = nullptr;
	m_renderFocus = false;
}
void Focus::AddNormalLayer() {
	if (m_PopUpLayerCounter == 0) {
		AddLayer();
	}
	else {
		m_toAdd.AddLayer();
		m_toAddDelete.push_back(true);
	}
}
void Focus::AddPopUpLayer() {
	AddLayer();
	++m_PopUpLayerCounter;
}
void Focus::DeleteLayer() {
	for (auto f : m_focus) {
		f->SetFocus(false);
	}

	m_focus.RemoveLayer();

	if (m_lastFocus.size() > 0) {
		SetSpecificFocus(m_lastFocus.at(m_lastFocus.size() - 1));
		m_lastFocus.pop_back();
		m_renderFocus = false;
	}
}
void Focus::DeleteNormalLayer() {
	if (m_PopUpLayerCounter == 0) {
		DeleteLayer();
	}
	else {
		m_toDelete.AddLayer();
		m_toAddDelete.push_back(false);
	}
}
void Focus::DeletePopUpLayer() {
	DeleteLayer();
	--m_PopUpLayerCounter;
	if (m_PopUpLayerCounter == 0) {
		SetLayerAfterPopUp();
	}
}

void Focus::AddElement(Focusable* focusable) {
	CheckNewID(focusable->GetFocusID());
	m_focus.AddElement(focusable);

	if (m_currentFocus) {
		m_currentFocus->SetFocus(false);
	}
	SetInitialFocus();
}
void Focus::AddNormalElement(Focusable* focusable) {
	if (m_PopUpLayerCounter == 0) {
		AddElement(focusable);
	}
	else {
		m_toAdd.AddElement(focusable);
	}
}
void Focus::AddPopUpElement(Focusable* focusable) {
	AddElement(focusable);
}
void Focus::DeleteElement(Focusable* focusable) {
	m_focus.RemoveElement(focusable);

	if (m_currentFocus == focusable) {
		m_currentFocus = GetNextFocus();
	}
}
void Focus::DeleteNormalElement(Focusable* focusable) {
	if (m_PopUpLayerCounter == 0) {
		DeleteElement(focusable);
	}
	else {
		m_toDelete.AddElement(focusable);
	}
}
void Focus::DeletePopUpElement(Focusable* focusable) {
	DeleteElement(focusable);
}

void Focus::SetLayerAfterPopUp() {
	//
	// TODO
	// -> implement this method
	// 
}

void Focus::CheckNewID(unsigned int newID) {
	for (auto focus : m_focus) {
		if (focus->GetFocusID() == newID) {
			throw std::invalid_argument("ID already exists, ID: " + newID);
		}
	}
}

Focus::Focus() {
	AddLayer();
	AppContext& appContext = AppContext::GetInstance();
	appContext.eventManager.AddListener(this);
}

void Focus::Clear() {
	m_focus.Clear();
	m_toAdd.Clear();
	m_toDelete.Clear();
	m_toAddDelete.clear();
	m_PopUpLayerCounter = 0;
	m_currentFocus = nullptr;
}

void Focus::OnEvent(Event const& event) {
	if (auto const focusEvent =dynamic_cast<NewFocusElementEvent const*>(&event)) {
		AddNormalElement(focusEvent->GetFocusable());
		return;
	}
	if (auto const focusEvent = dynamic_cast<NewFocusPopUpElementEvent const*>(&event)) {
		AddPopUpElement(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusElementEvent const*>(&event)) {
		DeleteNormalElement(focusEvent->GetFocusable());
		return;
	}
	if (auto const focusEvent = dynamic_cast<DeleteFocusPopUpElementEvent const*>(&event)) {
		DeletePopUpElement(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<SelectFocusElementEvent const*>(&event)) {
		SetSpecificFocus(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<NewFocusLayerEvent const*>(&event)) {
		AddNormalLayer();
		return;
	}
	if (auto const focusEvent = dynamic_cast<NewFocusPopUpLayerEvent const*>(&event)) {
		AddPopUpLayer();
		return;
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusLayerEvent const*>(&event)) {
		DeleteNormalLayer();
		return;
	}
	if (auto const focusEvent = dynamic_cast<DeleteFocusPopUpLayerEvent const*>(&event)) {
		DeletePopUpLayer();
		return;
	}

	if (auto const focusEvent = dynamic_cast<ClearFocusEvent const*>(&event)) {
		Clear();
		return;
	}
}

void Focus::CheckAndUpdate() {
	if (!m_currentFocus) {
		return;
	}

	if (IsKeyPressed(KEY_TAB)) {
		m_renderFocus = true;
		if (IsKeyDown(KEY_LEFT_SHIFT) or IsKeyDown(KEY_RIGHT_SHIFT)) {
			SetPreviousFocus();
			return;
		}
		SetNextFocus();
	}
}
void Focus::Render() {
	if (!m_currentFocus) { return; }
	if (!m_renderFocus) { return; }

	Rectangle const& f_colider = m_currentFocus->GetCollider();
	 float offset = 5.0;
	DrawRectangleLinesEx(
		Rectangle(
			static_cast<int>(f_colider.x) - offset,
			static_cast<int>(f_colider.y) - offset,
			static_cast<int>(f_colider.width) + 2.0f * offset,
			static_cast<int>(f_colider.height) + 2.0f * offset),
		offset,
		PURPLE
	);
}
