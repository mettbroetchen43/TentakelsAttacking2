//
// Purpur Tentakel
// 04.09.2022
//

#include "Focus.h"
#include "Focusable.h"
#include "UIEvents.h"
#include "AppContext.h"
#include <stdexcept>

void Focus::UnfocusAllAtTopLayer() {
	for (auto focus : m_focus) {
		focus->SetFocus(false);
	}

	m_currentFocus = nullptr;
}

Focusable* Focus::GetFirstFocus() {
	Focusable* firstFocus = nullptr;

	for (auto focus : m_focus) {
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

	for (auto focus : m_focus) {
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

	for (auto focus : m_focus) {
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

	for (auto focus : m_focus) {
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
void Focus::DeleteLayer() {
	m_focus.RemoveLayer();
	if (m_lastFocus.size() > 0) {
		SetSpecificFocus(m_lastFocus.at(m_lastFocus.size() - 1));
		m_lastFocus.pop_back();
		m_renderFocus = false;
	}

}

void Focus::AddElement(Focusable* focusable) {
	CheckNewID(focusable->GetFocusID());
	m_focus.AddElement(focusable);

	if (!m_currentFocus) {
		SetInitialFocus();
	}
}
void Focus::DeleteElement(Focusable* focusable) {
	if (m_currentFocus == focusable) {
		m_currentFocus = GetNextFocus();
	}

	m_focus.RemoveElement(focusable);
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
	m_currentFocus = nullptr;
}

void Focus::OnEvent(Event const& event) {
	if (auto const focusEvent = dynamic_cast<NewFocusElementEvent const*>(&event)) {
		AddElement(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusElementEvent const*>(&event)) {
		DeleteElement(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<SelectFocusElementEvent const*>(&event)) {
		SetSpecificFocus(focusEvent->GetFocusable());
		return;
	}

	if (auto const focusEvent = dynamic_cast<NewFocusLayerEvent const*>(&event)) {
		AddLayer();
		return;
	}

	if (auto const focusEvent = dynamic_cast<DeleteFocusLayerEvent const*>(&event)) {
		DeleteLayer();
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
